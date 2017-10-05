// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#import "IndoorAtlasLocationManagerObjC.h"
#import <IndoorAtlas/IALocationManager.h>
#include "LatLongAltitude.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "AppHost.h"
#include "AboutPageIndoorAtlasDataMessage.h"
#include <string>

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

typedef FailureHandler<IndoorAtlasLocationManagerObjC> FailureHandlerType;

@interface IndoorAtlasLocationManagerObjC()<IALocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
    ExampleApp::ExampleAppMessaging::TMessageBus* m_pMessageBus;
    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory *m_piOSAlertBoxFactory;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManagerObjC> > *m_failAlertHandler;
    
    std::string m_indoorAtlasFloorId;
    int m_eegeoFloorIndex;
    float m_latitude;
    float m_longitude;
}
@property (nonatomic, strong) IALocationManager *locationManager;
@end

@implementation IndoorAtlasLocationManagerObjC

-(instancetype) init: (ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService
          messageBus: (ExampleApp::ExampleAppMessaging::TMessageBus*) messageBus
  iOSAlertBoxFactory:(Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory*) iOSAlertBoxFactory
{
    if(self = [super init])
    {
        m_pIndoorAtlasLocationService = indoorAtlasLocationService;
        m_pMessageBus = messageBus;
        m_piOSAlertBoxFactory = iOSAlertBoxFactory;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManagerObjC> >(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
        
        m_pIndoorAtlasLocationService->SetIsAuthorized(true);
    }
    
    return self;
}

-(void) startUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
{
    self.locationManager = [IALocationManager sharedInstance];
    [self.locationManager setApiKey:apiKey andSecret:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
    
    m_pIndoorAtlasLocationService->SetIsAuthorized(true);
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0, 0);
    m_pIndoorAtlasLocationService->SetLocation(latLong);
    
    [self.locationManager startUpdatingLocation];
}

-(void) stopUpdatingLocation
{
    [self.locationManager stopUpdatingLocation];
}

-(void) dealloc
{
    m_pIndoorAtlasLocationService->SetIsAuthorized(false);
    
    [self.locationManager stopUpdatingLocation];
    self.locationManager.delegate = nil;
    delete m_failAlertHandler;
    delete m_failureHandlerWrapper;
    [super dealloc];
}

-(void) indoorLocationManager: (IALocationManager*) manager didUpdateLocations: (NSArray*) locations
{
    m_pIndoorAtlasLocationService->SetIsAuthorized(true);
    
    CLLocation *l = [(IALocation*)locations.lastObject location];
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(l.coordinate.latitude, l.coordinate.longitude);
    m_latitude = latLong.GetLatitudeInDegrees();
    m_longitude = latLong.GetLongitudeInDegrees();
    m_pIndoorAtlasLocationService->SetLocation(latLong);
    
    [self notifyUpdatedPosition];
}

-(void) indoorLocationManager: (IALocationManager*) manager didEnterRegion: (IARegion*) region
{
    m_pIndoorAtlasLocationService->SetIsAuthorized(true);
    
    if(region.type == kIARegionTypeFloorPlan)
    {
        NSString* floorPlanId = region.identifier;

        int floorIndex;
        if(![self tryGetFloorIndexFromFloorPlanId: std::string([floorPlanId UTF8String]) wrldFloorId:floorIndex])
        {
            floorIndex = -1;
        }
        m_eegeoFloorIndex = floorIndex;
        m_indoorAtlasFloorId = std::string([floorPlanId UTF8String]);
        m_pIndoorAtlasLocationService->SetFloorIndex(floorIndex);
        
    }
    [self notifyUpdatedPosition];
}

-(bool) tryGetFloorIndexFromFloorPlanId: (std::string) floorPlanId wrldFloorId:(int&)wrldFloorId
{
    for(std::map<int, std::string>::iterator it = m_floorMap.begin(); it != m_floorMap.end(); ++it)
    {
        if(it->second == floorPlanId)
        {
            wrldFloorId = it->first;
            return true;
        }
    }
    
    wrldFloorId = -1;
    return false;
}

- (void)notifyUpdatedPosition
{
    m_pMessageBus->Publish(ExampleApp::AboutPage::AboutPageIndoorAtlasDataMessage(m_eegeoFloorIndex, m_indoorAtlasFloorId, m_latitude, m_longitude));
}

- (void)indoorLocationManager:(nonnull IALocationManager *)manager statusChanged:(nonnull IAStatus *)status
{
    if(status.type == ia_status_type::kIAStatusServiceUnavailable)
    {
        /*
        m_piOSAlertBoxFactory->CreateSingleOptionAlertBox
        (
         "IndoorAtlas unavailable",
         "Recently lost connection to IndoorAtlas.",
         *m_failAlertHandler
         );
        //*/
    }
}

- (void)handleFailure
{
    
}

@end
