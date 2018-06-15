// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationServiceImpl.h"

#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorHeightHelpers.h"
#include "IPSConfigurationParser.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
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
    ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationServiceImpl* m_pIndoorAtlasLocationService;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManager>> *m_failAlertHandler;
}
@property (nonatomic, strong) IALocationManager *locationManager;
@end

@implementation IndoorAtlasLocationManager

-(instancetype) init: (ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationServiceImpl*) indoorAtlasLocationService
{
    if(self = [super init])
    {
        m_pIndoorAtlasLocationService = indoorAtlasLocationService;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<IndoorAtlasLocationManager> >(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
        
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


namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationServiceImpl::IndoorAtlasLocationServiceImpl(
                                                                           Eegeo::Location::ILocationService& defaultLocationService,
                                                                           ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                                                           const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                           const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_defaultLocationService(defaultLocationService)
                , m_pIndoorAtlasLocationManager(nullptr)
                , m_environmentFlatteningService(environmentFlatteningService)
                , m_messageBus(messageBus)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorMetaDataRepository(interiorMetaDataRepository)
                , m_isAuthorized(false)
                , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
                , m_pauseState(false, false, false)
                , m_floorIndex(-1)
                , m_horizontalAccuracy(0.0)
                , m_isActive(false)
                {
                    m_pIndoorAtlasLocationManager = [[IndoorAtlasLocationManager alloc] init: this];
                }
                
                IndoorAtlasLocationServiceImpl::~IndoorAtlasLocationServiceImpl()
                {
                    [m_pIndoorAtlasLocationManager release];
                    m_pIndoorAtlasLocationManager = nullptr;
                }
                
                void IndoorAtlasLocationServiceImpl::StartUpdating()
                {
                    StartUpdatingLocation();
                    StartUpdatingHeading();
                }
                
                void IndoorAtlasLocationServiceImpl::StopUpdating()
                {
                    StopUpdatingLocation();
                    StopUpdatingHeading();
                }
                
                void IndoorAtlasLocationServiceImpl::SetIsAuthorized(bool isAuthorized)
                {
                    m_isAuthorized = isAuthorized;
                }
                
                void IndoorAtlasLocationServiceImpl::SetIsActive(bool isActive)
                {
                    m_isActive = isActive;
                }
                
                void IndoorAtlasLocationServiceImpl::SetLocation(const Eegeo::Space::LatLong& latLong)
                {
                    SetIsAuthorized(true);
                    m_latLong = latLong;

                    PublishAboutPageIndoorAtlasDataMessage();
                }
                
                void IndoorAtlasLocationServiceImpl::SetHorizontalAccuracy(double radius)
                {
                    m_horizontalAccuracy = radius;
                }
                
                void IndoorAtlasLocationServiceImpl::SetFloor(const std::string& indoorAtlasFloorId, int floorIndex)
                {
                    m_indoorAtlasFloorId = indoorAtlasFloorId;
                    m_floorIndex = floorIndex;

                    PublishAboutPageIndoorAtlasDataMessage();
                }

                // todo loc: this should possibly be moved to the app domain -- maybe dangling off ICurrentLocationService a controller
                void IndoorAtlasLocationServiceImpl::PublishAboutPageIndoorAtlasDataMessage()
                {
                    m_messageBus.Publish(ExampleApp::AboutPage::AboutPageIndoorAtlasDataMessage(
                            m_floorIndex, m_indoorAtlasFloorId, m_latLong.GetLatitudeInDegrees(), m_latLong.GetLongitudeInDegrees()));
                }

                void IndoorAtlasLocationServiceImpl::OnPause()
                {
                    if(m_pauseState.isPaused)
                    {
                        return;
                    }
                    
                    m_pauseState = PauseState(true, m_isActive, m_isActive);
                    
                    StopUpdatingLocation();
                    StopUpdatingHeading();
                }
                
                void IndoorAtlasLocationServiceImpl::OnResume()
                {
                    if(!m_pauseState.isPaused)
                    {
                        return;
                    }
                    
                    m_pauseState.isPaused = false;
                    
                    if(m_pauseState.wasUpdatingLocation)
                    {
                        StartUpdatingLocation();
                    }
                    
                    if(m_pauseState.wasUpdatingHeading)
                    {
                        StartUpdatingHeading();
                    }
                }
                
                bool IndoorAtlasLocationServiceImpl::IsLocationAuthorized() const
                {
                    return m_isAuthorized;
                }
                
                bool IndoorAtlasLocationServiceImpl::IsLocationActive() const
                {
                    return m_isActive;
                }
                
                bool IndoorAtlasLocationServiceImpl::GetLocation(Eegeo::Space::LatLong &latlong) const
                {
                    latlong.SetLatitude(m_latLong.GetLatitude());
                    latlong.SetLongitude(m_latLong.GetLongitude());
                    return true;
                }
                
                bool IndoorAtlasLocationServiceImpl::GetAltitude(double &altitude) const
                {
                    const auto* interiorModel = m_interiorInteractionModel.GetInteriorModel();
                    
                    if(interiorModel)
                    {
                        Eegeo_ASSERT(m_floorIndex >= 0, "invalid floor index");
                        
                        altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(
                                                                                                                                         *interiorModel,
                                                                                                                                         static_cast<unsigned int>(m_floorIndex),
                                                                                                                                         m_environmentFlatteningService.GetCurrentScale());
                        
                        return true;
                    }
                    
                    return false;
                }
                
                bool IndoorAtlasLocationServiceImpl::GetHorizontalAccuracy(double &accuracy) const
                {
                    accuracy = m_horizontalAccuracy;
                    return true;
                }
                
                void IndoorAtlasLocationServiceImpl::StartUpdatingLocation()
                {
                    if(m_isActive)
                    {
                        return;
                    }
                    
                    const auto interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    
                    if(!interiorId.IsValid())
                    {
                        return;
                    }
                    
                    // todo loc : duplicate code
                    typedef std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;
                    TrackingInfoMap trackingInfoMap;
                    ExampleApp::InteriorsPosition::TryAndGetInteriorTrackingInfo(trackingInfoMap, interiorId, m_interiorMetaDataRepository);
                    
                    const TrackingInfoMap::const_iterator trackingInfoEntry = trackingInfoMap.find(interiorId.Value());
                    
                    if (trackingInfoEntry == trackingInfoMap.end())
                    {
                        return;
                    }
                    
                    const auto& trackingInfo = trackingInfoEntry->second;
                    
                    if (trackingInfo.GetType() != "IndoorAtlas")
                    {
                        return;
                    }
                    
                    const std::string& apiKey = trackingInfo.GetConfig().GetApiKey();
                    const std::string& apiSecret = trackingInfo.GetConfig().GetApiSecret();
                    const std::map<int, std::string>& floorMap = trackingInfo.GetFloorIndexMap();
                    
                    NSString* apiKeyNSString = [NSString stringWithCString:apiKey.c_str() encoding:[NSString defaultCStringEncoding]];
                    NSString* apiSecretNSString = [NSString stringWithCString:apiSecret.c_str() encoding:[NSString defaultCStringEncoding]];
                    
                    [m_pIndoorAtlasLocationManager startUpdatingLocation: apiKeyNSString apiSecret: apiSecretNSString floorMap: floorMap];
                    SetIsActive(true);
                }
                
                void IndoorAtlasLocationServiceImpl::StopUpdatingLocation()
                {
                    if(!m_isActive)
                    {
                        return;
                    }
                    
                    [m_pIndoorAtlasLocationManager stopUpdatingLocation];
                    SetIsActive(false);
                }
                
                bool IndoorAtlasLocationServiceImpl::GetHeadingDegrees(double &headingDegrees) const
                {
                    // indoor atlas just provides location; fall back to default for heading
                    return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
                }
                
                bool IndoorAtlasLocationServiceImpl::IsHeadingAuthorized() const
                {
                    return m_isAuthorized;
                }
                
                bool IndoorAtlasLocationServiceImpl::IsHeadingActive() const
                {
                    return m_isActive;
                }
                
                void IndoorAtlasLocationServiceImpl::StartUpdatingHeading()
                {
                    m_defaultLocationService.StartUpdatingHeading();
                }
                
                void IndoorAtlasLocationServiceImpl::StopUpdatingHeading()
                {
                    m_defaultLocationService.StopUpdatingHeading();
                }
                
                bool IndoorAtlasLocationServiceImpl::IsIndoors() const
                {
                    return true;
                }
                
                Eegeo::Resources::Interiors::InteriorId IndoorAtlasLocationServiceImpl::GetInteriorId() const
                {
                    return m_interiorInteractionModel.HasInteriorModel() ?
                    m_interiorInteractionModel.GetInteriorModel()->GetId() :
                    Eegeo::Resources::Interiors::InteriorId::NullId();
                }
                
                bool IndoorAtlasLocationServiceImpl::GetFloorIndex(int &floorIndex) const
                {
                    floorIndex = m_floorIndex;
                    return true;
                }
                
                bool IndoorAtlasLocationServiceImpl::IsIndoorAuthorized() const
                {
                    return m_isAuthorized;
                }
            }
        }
    }
}
