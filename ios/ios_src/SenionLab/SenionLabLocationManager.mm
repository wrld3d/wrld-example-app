// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#import "SenionLabLocationManager.h"
#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>
#import <SLIndoorLocation/SLSenionLocationSource.h>
#include "LatLongAltitude.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "AppHost.h"
#include "AboutPageViewModel.h"

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

@interface SenionLabLocationManager()<SLIndoorLocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    int m_floorIndex;
    ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
    SLLocationAvailability m_lastLocationAvailability;
    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory *m_piOSAlertBoxFactory;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>> *m_failAlertHandler;
    ExampleApp::ExampleAppMessaging::TMessageBus* m_messageBus;
}
@property (nonatomic, strong) SLIndoorLocationManager *locationManager;
@end

@implementation SenionLabLocationManager

-(instancetype) Init: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService*) senionLabLocationService
  iOSAlertBoxFactory:(Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory*) iOSAlertBoxFactory
          messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus*) messageBus
{
    m_lastLocationAvailability = SLLocationAvailabilityNotAvailable;
    if(self = [super init])
    {
        m_pSenionLabLocationService = senionLabLocationService;
        m_piOSAlertBoxFactory = iOSAlertBoxFactory;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>>(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
        m_messageBus = messageBus;
    }
    
    return self;
}

-(void) StartUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap
{
    [SLIndoorLocationManager setIbeaconAuthorizationMethod:SLRequestWhenInUseAuthorization];
    self.locationManager = [SLIndoorLocationManager defaultIndoorLocationMangerWithMapKey:apiKey customerId:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
    
    Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0, 0);
    m_pSenionLabLocationService->SetLocation(latLong);
}

-(void) StopUpdatingLocation
{
    [self.locationManager stopUpdatingLocation];
}

-(void) dealloc
{
    [self.locationManager stopUpdatingLocation];
    [self.locationManager release];
    [super dealloc];
}

-(void) didFinishLoadingManager
{
    [self.locationManager startUpdatingLocation];
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

-(void) didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius
{
}

-(void) didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius locationSource:(SLLocationSource *)locationSource
{
    if(locationSource != nil && [locationSource isKindOfClass:[SLSenionLocationSource class]])
    {
        m_pSenionLabLocationService->SetIsAuthorized(true);
        
        Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(location.latitude, location.longitude);
        m_pSenionLabLocationService->SetLocation(latLong);
        
        int floorIndex = [self getFloorIndexFromSenionFloorIndex:std::to_string(location.floorNr)];
        m_pSenionLabLocationService->SetFloorIndex(floorIndex);
        
        m_messageBus->Publish(ExampleApp::AboutPage::AboutPageSenionDataMessage(floorIndex, location.floorNr, location.latitude, location.longitude));
    }
}

-(void) didUpdateLocationAvailability:(SLLocationAvailability)locationAvailability
{
    if(locationAvailability != m_lastLocationAvailability)
    {
        m_lastLocationAvailability = locationAvailability;
        if(locationAvailability == SLLocationAvailabilityNotAvailable)
        {
            /*
            m_piOSAlertBoxFactory->CreateSingleOptionAlertBox
            (
             "Senion unavailable",
             "Recently lost connection to Senion.",
             *m_failAlertHandler
             );
            //*/
        }
        if(locationAvailability == SLLocationAvailabilityAvailable)
        {
            /*
            m_piOSAlertBoxFactory->CreateSingleOptionAlertBox
            (
             "Senion available",
             "Recently connected to Senion indoor positioning.",
             *m_failAlertHandler
             );
            //*/
        }
    }
}

-(void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

-(void) didUpdateMotionType:(SLMotionState)motionState
{
    m_pSenionLabLocationService->SetIsAuthorized(true);
}

-(void) didFailInternetConnectionWithError:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInternetConnectionWithError");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailInvalidIds:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInvalidIds");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailLocationAuthorizationStatus
{
    NSLog(@"SenionLabLocationManager didFailLocationAuthorizationStatus");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(void) didFailScanningBT
{
    NSLog(@"SenionLabLocationManager didFailScanningBT");
    m_pSenionLabLocationService->SetIsAuthorized(false);
}

-(int) getFloorIndexFromSenionFloorIndex: (std::string) senionFloorIndex
{
    for(std::map<int, std::string>::iterator it = m_floorMap.begin(); it != m_floorMap.end(); ++it)
    {
        if(it->second == senionFloorIndex)
        {
            return it->first;
        }
    }
    
    return -1;
}

- (void)handleFailure
{
    
}

@end
