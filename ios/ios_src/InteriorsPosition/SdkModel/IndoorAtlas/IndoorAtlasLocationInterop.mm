// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationInterop.h"

#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorHeightHelpers.h"
#include "IPSConfigurationParser.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "IndoorAtlasLocationService.h"

#include <string>
#include <map>

#import <IndoorAtlas/IALocationManager.h>

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

typedef FailureHandler<IndoorAtlasLocationManager> FailureHandlerType;

@interface IndoorAtlasLocationManager()<IALocationManagerDelegate>
{
    std::map<int, std::string> m_floorMap;
    ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManager>> *m_failAlertHandler;
}
@property (nonatomic, strong) IALocationManager *locationManager;
@end

@implementation IndoorAtlasLocationManager

-(instancetype) init
{
    if(self = [super init])
    {
        m_pIndoorAtlasLocationService = nullptr;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManager> >(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
    }
    
    return self;
}

-(void) setLocationService: (ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService;
{
    m_pIndoorAtlasLocationService = indoorAtlasLocationService;
}

-(void) startUpdating: (NSString*) apiKey
            apiSecret: (NSString*) apiSecret
             floorMap: (std::map<int, std::string>) floorMap
{
    self.locationManager = [IALocationManager sharedInstance];
    [self.locationManager setApiKey:apiKey andSecret:apiSecret];
    self.locationManager.delegate = self;
    
    m_floorMap = floorMap;
    
    [self.locationManager startUpdatingLocation];
}

-(void) stopUpdating
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
    auto* l = [(IALocation*)locations.lastObject location];
    
    m_pIndoorAtlasLocationService->SetLocation(Eegeo::Space::LatLong::FromDegrees(
                                                                                  l.coordinate.latitude, l.coordinate.longitude));
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
        
        m_pIndoorAtlasLocationService->SetFloor(std::string([floorPlanId UTF8String]), floorIndex);
    }
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

- (void) indoorLocationManager:(nonnull IALocationManager *)manager statusChanged:(nonnull IAStatus *)status
{
    const bool isAuthorized = status.type == ia_status_type::kIAStatusServiceAvailable || 
                              status.type == ia_status_type::kIAStatusServiceLimited;

    m_pIndoorAtlasLocationService->SetIsAuthorized(isAuthorized);
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
            namespace IndoorAtlas
            {
                IndoorAtlasLocationInterop::IndoorAtlasLocationInterop()
                : m_pManager([[IndoorAtlasLocationManager alloc] init])
                {
                    
                }
                
                IndoorAtlasLocationInterop::~IndoorAtlasLocationInterop()
                {
                    [m_pManager dealloc];
                }
                
                void IndoorAtlasLocationInterop::SetLocationService(IndoorAtlasLocationService* pIndoorAtlasLocationManager)
                {
                    Eegeo_ASSERT(pIndoorAtlasLocationManager != nullptr);
                    [m_pManager setLocationService: pIndoorAtlasLocationManager];
                }
                
                void IndoorAtlasLocationInterop::StartUpdating(const std::string& apiKey,
                                                               const std::string& apiSecret,
                                                               const std::map<int, std::string>& floorMap)
                {
                    [m_pManager startUpdating: [NSString stringWithUTF8String:apiKey.c_str()]
                                    apiSecret: [NSString stringWithUTF8String:apiSecret.c_str()]
                                     floorMap: floorMap];
                }
                
                void IndoorAtlasLocationInterop::StopUpdating()
                {
                    [m_pManager stopUpdating];
                }
            }
        }
    }
}

