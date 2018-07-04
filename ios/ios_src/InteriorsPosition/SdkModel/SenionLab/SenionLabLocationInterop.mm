#include "SenionLabLocationInterop.h"

#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>
#import <SLIndoorLocation/SLSenionLocationSource.h>
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "SenionLabLocationService.h"

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
    
    ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
    SLLocationAvailability m_lastLocationAvailability;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>> *m_failAlertHandler;
}
@property (nonatomic, strong) SLIndoorLocationManager *locationManager;
@end

@implementation SenionLabLocationManager

-(instancetype) init
{
    m_lastLocationAvailability = SLLocationAvailabilityNotAvailable;
    if(self = [super init])
    {
        m_pSenionLabLocationService = nullptr;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>>(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
    }
    
    return self;
}

-(void) setLocationService: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService*) senionLocationService
{
    m_pSenionLabLocationService = senionLocationService;
}

-(void) startUpdating: (NSString*) apiKey
            apiSecret: (NSString*) apiSecret
             floorMap: (std::map<int, std::string>) floorMap
{
    [SLIndoorLocationManager setIbeaconAuthorizationMethod:SLRequestWhenInUseAuthorization];
    self.locationManager = [SLIndoorLocationManager defaultIndoorLocationMangerWithMapKey:apiKey customerId:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
}

-(void) stopUpdating
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
    if (locationSource == nil || ![locationSource isKindOfClass:[SLSenionLocationSource class]])
    {
        return;
    }
    
    const auto latLong = Eegeo::Space::LatLong::FromDegrees(location.latitude, location.longitude);
    const int wrldFloorIndex = [self getFloorIndexFromSenionFloorIndex:std::to_string(location.floorNr)];
    
    m_pSenionLabLocationService->SetLocationFromSenionData(latLong, location.floorNr, wrldFloorIndex, radius);
}

-(void) didUpdateLocationAvailability:(SLLocationAvailability)locationAvailability
{
    if(locationAvailability != m_lastLocationAvailability)
    {
        m_lastLocationAvailability = locationAvailability;
                
        if(locationAvailability == SLLocationAvailabilityNotAvailable)
        {
            m_pSenionLabLocationService->SetIsAuthorized(false);
        }
        
        if(locationAvailability == SLLocationAvailabilityAvailable)
        {
            m_pSenionLabLocationService->SetIsAuthorized(true);
        }
    }
}

-(void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{    
    if(m_lastLocationAvailability == SLLocationAvailabilityAvailable)
    {
        m_pSenionLabLocationService->SetHeadingFromSenionData(heading, status);
    }
}

-(void) didUpdateMotionType:(SLMotionState)motionState
{
    if(m_lastLocationAvailability == SLLocationAvailabilityAvailable)
    {
        m_pSenionLabLocationService->SetIsAuthorized(true);
    }    
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

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationInterop::SenionLabLocationInterop()
                : m_pManager([[SenionLabLocationManager alloc] init])
                {
                    
                }
                
                SenionLabLocationInterop::~SenionLabLocationInterop()
                {
                    [m_pManager dealloc];
                }
                
                void SenionLabLocationInterop::SetLocationService(SenionLabLocationService* pSenionLabLocationService)
                {
                    Eegeo_ASSERT(pSenionLabLocationService != nullptr);
                    [m_pManager setLocationService: pSenionLabLocationService];
                }
                
                void SenionLabLocationInterop::StartUpdatingLocation(const std::string& apiKey,
                                                                     const std::string& apiSecret,
                                                                     const std::map<int, std::string>& floorMap)
                {
                    [m_pManager startUpdating: [NSString stringWithUTF8String:apiKey.c_str()]
                                    apiSecret: [NSString stringWithUTF8String:apiSecret.c_str()]
                                     floorMap: floorMap];
                }
                
                void SenionLabLocationInterop::StopUpdatingLocation()
                {
                    [m_pManager stopUpdating];
                }
            }
        }
    }
}
