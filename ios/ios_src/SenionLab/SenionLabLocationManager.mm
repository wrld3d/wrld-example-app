// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#import "SenionLabLocationManager.h"
#import <StepInsideSdk/StepInsideSdk.h>
#include "LatLongAltitude.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "AppHost.h"
#include "AboutPageViewModel.h"
#import <objc/runtime.h>

template <typename T>
class FailureHandler
{
public:
    FailureHandler(T* pContext) : m_pContext(pContext) {}
    void HandleFailure()
    {
        [m_pContext handleFailure];
    }
private:
    T* m_pContext;
};

typedef FailureHandler<SenionLabLocationManager> FailureHandlerType;

@interface SenionLabLocationManager()<SSIStepInsideSdkStatusDelegate, SSIPositioningApiDelegate>
{
    std::map<std::string, std::map<int, std::vector<std::string> > > m_floorMap; // TJ: This looks somewhat interesting.... This needs the bullet. Boy scout later.
    std::map<std::string, Eegeo::Resources::Interiors::InteriorId> m_interiorIdMap;
    int m_floorIndex;
    ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
    SSILocationAvailability m_lastLocationAvailability;
    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory *m_piOSAlertBoxFactory;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>> *m_failAlertHandler;
    ExampleApp::ExampleAppMessaging::TMessageBus* m_messageBus;
    NSString* m_customerId;
}
@property (nonatomic, strong) SSIStepInsideSdkManager *stepInsideManager;
@property (nonatomic, strong) SSIStepInsideSdk *stepInside;
@end

@implementation SenionLabLocationManager

-(instancetype) Init: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService*) senionLabLocationService
  iOSAlertBoxFactory:(Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory*) iOSAlertBoxFactory
          messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus*) messageBus
{
    m_lastLocationAvailability = SSILocationAvailabilityNotAvailable;
    if(self = [super init])
    {
        m_pSenionLabLocationService = senionLabLocationService;
        m_piOSAlertBoxFactory = iOSAlertBoxFactory;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>>(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
        m_messageBus = messageBus;
        [self disableUploadBeaconList];
    }
    
    return self;
}

-(void) StartUpdatingLocation: (NSArray<NSString*>*) mapKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<std::string, std::map<int, std::vector<std::string> > >) floorMap
                interiorIdMap: (std::map<std::string, Eegeo::Resources::Interiors::InteriorId>) interiorIdMap
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self StartSenion: mapKey apiSecret:apiSecret floorMap:floorMap interiorIdMap:interiorIdMap];
    });
}

-(void) StartSenion: (NSArray<NSString*>*) mapKey
          apiSecret: (NSString*) apiSecret
           floorMap: (std::map<std::string, std::map<int, std::vector<std::string> > >) floorMap
      interiorIdMap: (std::map<std::string, Eegeo::Resources::Interiors::InteriorId>) interiorIdMap
{
    [SSISensors requestCoreLocationWhenInUseAuthorization];
    
    self.stepInsideManager = [SSIStepInsideSdkManager managerWithConfig:^(SSIStepInsideSdkManagerConfig * _Nonnull config)
    {
        NSMutableArray<SSIMapKey*>* mapKeyArray = [[NSMutableArray<SSIMapKey*> alloc] init];
        for(NSString* key in mapKey)
        {
            [mapKeyArray addObject:[[SSIMapKey alloc] initWithValue:key]];
        }
        
        [config withApiKey:[[SSIApiKey alloc] initWithValue:apiSecret]];
        [config withMapKeys:mapKeyArray];
    }];
    
    [self.stepInsideManager loadSdk];
    
    self.stepInside = [self.stepInsideManager attachHighPerformanceMode];
    
    [self.stepInside addStatusDelegate:self];
    [self.stepInside.positioning addDelegate:self];
    [self.stepInside start];
    
    m_floorMap = floorMap;
    m_interiorIdMap = interiorIdMap;
    m_customerId = apiSecret;
    
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0, 0);
    m_pSenionLabLocationService->SetLocation(latLong);
    m_pSenionLabLocationService->SetInteriorId(Eegeo::Resources::Interiors::InteriorId::NullId());
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

- (void) disableUploadBeaconList {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        //Strategy is to replace the method that does the uploading with our own using method swizzeling.
        // get self class, we use it later for the replaceMethod, we need it to set up the class of
        // the funciton that we are going to redirect.
        Class cclass = [self class];
        
        Class SLObserverBeaconDataTask = objc_getClass("SLObservedBeaconDataTask");
        if (SLObserverBeaconDataTask == 0) {
            return;
        }
        
        SEL replacedSelector = @selector(uploadBeaconServerDataList:);
        Method replacedMethod = class_getInstanceMethod(cclass, replacedSelector);
        
        unsigned int methodCount = 0;
        Method *methodList = class_copyMethodList(SLObserverBeaconDataTask, &methodCount);
        for (int i = 0; i < methodCount; i++){
            Method method_obj = methodList[i];
            SEL selector = method_getName(method_obj);
            const char * method = sel_getName(selector);
            // we check on the methods that is the function that we want to hook.
            if (strcmp("uploadBeaconServerDataList:completion:", method) == 0){
                class_replaceMethod(SLObserverBeaconDataTask, selector, method_getImplementation(replacedMethod), method_getTypeEncoding(method_obj));
            }
        }
    });
}

- (void)uploadBeaconServerDataList:(id)completion {
    //empty implementation to prevent upload of private data to senion services
}

-(void) StopUpdatingLocation
{
    [self.stepInside stop];
    [self.stepInside removeStatusDelegate:self];
    [self.stepInside.positioning removeDelegate:self];
    self.stepInside = nil;
    self.stepInsideManager = nil;
}

-(void) dealloc
{
    [self StopUpdatingLocation];
    [super dealloc];
}

- (void)positioningApi:(SSIPositioningApi *)positioningApi didUpdateLocation:(SSILocation *)location
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self locationUpdate: location];
    });
}

- (void)locationUpdate:(SSILocation *)location
{
    if(location != nil && [location.source isKindOfClass:[SSISenionLocationSource class]])
    {
        m_pSenionLabLocationService->SetIsAuthorized(true);
        
        Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(location.latitude, location.longitude);
        m_pSenionLabLocationService->SetLocation(latLong);
        
        std::string mapKey = std::string([static_cast<SSISenionLocationSource*>(location.source).mapKey.value UTF8String]);
        std::string floorId = std::string([location.floorId.value UTF8String]);
        int floorIndex = [self getFloorIndexFromSenionFloorIndex:floorId senionMapKey:mapKey];
        m_pSenionLabLocationService->SetFloorIndex(floorIndex);
        
        std::map<std::string, Eegeo::Resources::Interiors::InteriorId>::iterator it = m_interiorIdMap.find(mapKey);
        
        if(it != m_interiorIdMap.end() && m_pSenionLabLocationService->GetInteriorId() != it->second)
        {
            m_pSenionLabLocationService->SetInteriorId(it->second);
            
            std::map<std::string, std::map<int, std::vector<std::string>>>::iterator floor_it = m_floorMap.find(mapKey);
            if(floor_it != m_floorMap.end())
            {
                m_messageBus->Publish(ExampleApp::AboutPage::AboutPageSenionSettingsTypeMessage(mapKey, std::string([m_customerId UTF8String]), floor_it->second, it->second.Value()));
            }
        }
        
        m_messageBus->Publish(ExampleApp::AboutPage::AboutPageSenionDataTypeMessage(floorIndex, floorId, location.latitude, location.longitude));
    }
}

- (void)positioningApi:(SSIPositioningApi *)positioningApi didUpdateHeading:(SSIHeading *)heading
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self headingUpdate: heading];
    });
}

- (void)headingUpdate:(SSIHeading *)heading
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
    m_pSenionLabLocationService->SetHeadingDegrees([heading angle]);
}

- (void)positioningApi:(SSIPositioningApi *)positioningApi didUpdateLocationAvailability:(SSILocationAvailability)locationAvailability
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self availabilityUpdate: locationAvailability];
    });
}

- (void)availabilityUpdate:(SSILocationAvailability)locationAvailability
{
    if(locationAvailability != m_lastLocationAvailability)
    {
        m_lastLocationAvailability = locationAvailability;
        if(locationAvailability == SSILocationAvailabilityNotAvailable)
        {
            /*
            m_piOSAlertBoxFactory->CreateSingleOptionAlertBox
            (
             "Senion unavailable",
             "Recently lost connection to Senion.",
             *m_failAlertHandler
             );
            //*/
            
            m_pSenionLabLocationService->SetIsLocationAvailable(false);
            m_messageBus->Publish(ExampleApp::AboutPage::AboutPageIndoorPositionTypeMessage("\nIndoor positioning type: GPS"));
        }
        if(locationAvailability == SSILocationAvailabilityAvailable)
        {
            /*
            m_piOSAlertBoxFactory->CreateSingleOptionAlertBox
            (
             "Senion available",
             "Recently connected to Senion indoor positioning.",
             *m_failAlertHandler
             );
            //*/
            
            m_pSenionLabLocationService->SetIsLocationAvailable(true);
            m_messageBus->Publish(ExampleApp::AboutPage::AboutPageIndoorPositionTypeMessage("\nIndoor positioning type: Senion"));
        }
    }
}

- (void) positioningApi:(SSIPositioningApi *)positioningApi didUpdateMotionType:(SSIMotionType)motionType
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self motionTypeUpdate: motionType];
    });
}

- (void) motionTypeUpdate:(SSIMotionType)motionType
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

- (void) stepInsideSdk:(SSIStepInsideSdk *)stepInsideSdk didFailWithError:(NSError *)error
{
    switch(error.code)
    {
        case SSIStepInsideSdkErrorTypeInvalidKeys:
            NSLog(@"SenionLabLocationManager didFailWithError: InvalidKeys");
            break;
        case SSIStepInsideSdkErrorTypeBleNotEnabled:
            NSLog(@"SenionLabLocationManager didFailWithError: BleNotEnabled");
            break;
        case SSIStepInsideSdkErrorTypeLocationFailed:
            NSLog(@"SenionLabLocationManager didFailWithError: LocationFailed");
            break;
        case SSIStepInsideSdkErrorTypeFailedToLoadGeoMessengerData:
            NSLog(@"SenionLabLocationManager didFailWithError: FailedToLoadGeoMessengerData");
            break;
        case SSIStepInsideSdkErrorTypeFailedToLoadPositioningPackage:
            NSLog(@"SenionLabLocationManager didFailWithError: FailedToLoadPositioningPackage");
            break;
        case SSIStepInsideSdkErrorTypeCoreLocationAuthorizationDenied:
            NSLog(@"SenionLabLocationManager didFailWithError: CoreLocationAuthorizationDenied");
            m_pSenionLabLocationService->SetIsAuthorized(false);
            break;
        case SSIStepInsideSdkErrorTypeCoreLocationAuthorizationNotDetermined:
            NSLog(@"SenionLabLocationManager didFailWithError: CoreLocationAuthorizationNotDetermined");
            m_pSenionLabLocationService->SetIsAuthorized(false);
            break;
    }
}

-(int) getFloorIndexFromSenionFloorIndex: (std::string) senionFloorIndex senionMapKey: (std::string) senionMapKey
{
    std::map<std::string, std::map<int, std::vector<std::string> > >::iterator mapKey_it = m_floorMap.find(senionMapKey);

    if(mapKey_it != m_floorMap.end())
    {
        for(std::map<int, std::vector<std::string> >::iterator floor_it = mapKey_it->second.begin(); floor_it != mapKey_it->second.end(); ++floor_it)
        {
            for(std::vector<std::string>::iterator possible_target_it = floor_it->second.begin();
                possible_target_it != floor_it->second.end();
                ++possible_target_it)
            {
                if(*possible_target_it == senionFloorIndex)
                {
                    return floor_it->first;
                }
            }
        }
    }
    
    return -1;
}

- (void)handleFailure
{
    
}

@end
