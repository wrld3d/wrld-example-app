// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#include "SenionLabLocationServiceImpl.h"

#include "ApplicationInteriorTrackingInfo.h"
#include "EnvironmentFlatteningService.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorHeightHelpers.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "IPSConfigurationParser.h"
#include "ILocationService.h"

#import <SLIndoorLocation/SLCoordinate3D.h>
#import <SLIndoorLocation/SLIndoorLocationManager.h>
#import <SLIndoorLocation/SLSenionLocationSource.h>

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

    ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationServiceImpl* m_pSenionLabLocationServiceImpl;
    SLLocationAvailability m_lastLocationAvailability;
    FailureHandlerType *m_failureHandlerWrapper;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>> *m_failAlertHandler;
}
@property (nonatomic, strong) SLIndoorLocationManager *locationManager;
@end

@implementation SenionLabLocationManager

-(instancetype) init: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationServiceImpl*) senionLabLocationService
{
    m_lastLocationAvailability = SLLocationAvailabilityNotAvailable;
    if(self = [super init])
    {
        m_pSenionLabLocationServiceImpl = senionLabLocationService;
        m_failureHandlerWrapper = new FailureHandlerType(self);
        m_failAlertHandler = new Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FailureHandler<SenionLabLocationManager>>(m_failureHandlerWrapper, &FailureHandlerType::HandleFailure);
    }

    return self;
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
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(true);
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

    m_pSenionLabLocationServiceImpl->SetLocationFromSenionData(latLong, location.floorNr, wrldFloorIndex, radius);
}

-(void) didUpdateLocationAvailability:(SLLocationAvailability)locationAvailability
{
    if(locationAvailability != m_lastLocationAvailability)
    {
        m_lastLocationAvailability = locationAvailability;
        if(locationAvailability == SLLocationAvailabilityNotAvailable)
        {

        }

        if(locationAvailability == SLLocationAvailabilityAvailable)
        {

        }
    }
}

-(void) didUpdateHeading:(double)heading withStatus:(BOOL)status
{
    m_pSenionLabLocationServiceImpl->SetHeadingFromSenionData(heading, status);
}

-(void) didUpdateMotionType:(SLMotionState)motionState
{
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(true);
}

-(void) didFailInternetConnectionWithError:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInternetConnectionWithError");
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(false);
}

-(void) didFailInvalidIds:(NSError *)error
{
    NSLog(@"SenionLabLocationManager didFailInvalidIds");
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(false);
}

-(void) didFailLocationAuthorizationStatus
{
    NSLog(@"SenionLabLocationManager didFailLocationAuthorizationStatus");
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(false);
}

-(void) didFailScanningBT
{
    NSLog(@"SenionLabLocationManager didFailScanningBT");
    m_pSenionLabLocationServiceImpl->SetIsAuthorized(false);
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
                SenionLabLocationServiceImpl::SenionLabLocationServiceImpl(
                        Eegeo::Location::ILocationService& defaultLocationService,
                        ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                        const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                        const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_defaultLocationService(defaultLocationService)
                , m_pSenionLabLocationManager(nullptr)
                , m_environmentFlatteningService(environmentFlatteningService)
                , m_messageBus(messageBus)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorMetaDataRepository(interiorMetaDataRepository)
                , m_location(Eegeo::Space::LatLong::FromDegrees(0, 0))
                , m_pauseState(false, false, false)
                , m_horizontalAccuracy(0.0)
                , m_headingDegrees(0.0)
                , m_senionFloorNumber(-1)
                , m_wrldFloorIndex(-1)
                , m_isAuthorized(false)
                , m_isLocationActive(false)
                , m_isHeadingActive(false)
                {
                    m_pSenionLabLocationManager = [[SenionLabLocationManager alloc] init: this];
                }

                SenionLabLocationServiceImpl::~SenionLabLocationServiceImpl()
                {
                    [m_pSenionLabLocationManager release];
                    m_pSenionLabLocationManager = nullptr;
                }

                bool SenionLabLocationServiceImpl::IsActive() const
                {
                    return m_isHeadingActive || m_isLocationActive;
                }

                void SenionLabLocationServiceImpl::StartUpdating()
                {
                    if(IsActive())
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

                    if (trackingInfo.GetType() != "Senion")
                    {
                        return;
                    }

                    const std::string& apiKey = trackingInfo.GetConfig().GetApiKey();
                    const std::string& apiSecret = trackingInfo.GetConfig().GetApiSecret();
                    const std::map<int, std::string>& floorMap = trackingInfo.GetFloorIndexMap();

                    NSString* apiKeyNSString = [NSString stringWithCString:apiKey.c_str() encoding:[NSString defaultCStringEncoding]];
                    NSString* apiSecretNSString = [NSString stringWithCString:apiSecret.c_str() encoding:[NSString defaultCStringEncoding]];

                    [m_pSenionLabLocationManager startUpdating: apiKeyNSString apiSecret: apiSecretNSString floorMap: floorMap];
                    
                    m_defaultLocationService.StopUpdatingLocation();
                    
                    // todo: heading configuration -- only use heading if configured to do so
                    m_defaultLocationService.StopUpdatingHeading();
                    
                    m_isHeadingActive = true;
                    m_isLocationActive = true;
                }

                void SenionLabLocationServiceImpl::StopUpdating()
                {
                    if(!IsActive())
                    {
                        return;
                    }

                    m_isLocationActive = false;
                    m_isHeadingActive = false;

                    [m_pSenionLabLocationManager stopUpdating];
                }

                void SenionLabLocationServiceImpl::SetIsAuthorized(bool isAuthorized)
                {
                    m_isAuthorized = isAuthorized;
                }

                void SenionLabLocationServiceImpl::SetLocationFromSenionData(
                        const Eegeo::Space::LatLong &latLong,
                        int senionFloorNumber,
                        int wrldFloorIndex,
                        double horizontalAccuracy)
                {
                    SetIsAuthorized(true);
                    m_location = latLong;
                    m_senionFloorNumber = senionFloorNumber;
                    m_wrldFloorIndex = wrldFloorIndex;
                    m_horizontalAccuracy = horizontalAccuracy;

                    PublishAboutPageSenionDataMessage();
                }

                void SenionLabLocationServiceImpl::SetHeadingFromSenionData(double headingDegrees, bool isAccurate)
                {
                    SetIsAuthorized(true);

                    if(isAccurate) // todo loc: test this more; first stab
                    {
                        m_headingDegrees = headingDegrees;
                    }
                }

                // todo loc: this should possibly be moved to the app domain
                void SenionLabLocationServiceImpl::PublishAboutPageSenionDataMessage()
                {
                    m_messageBus.Publish(ExampleApp::AboutPage::AboutPageSenionDataMessage(
                            m_wrldFloorIndex, m_senionFloorNumber, m_location.GetLatitudeInDegrees(), m_location.GetLongitudeInDegrees()));
                }

                void SenionLabLocationServiceImpl::OnPause()
                {
                    if(m_pauseState.isPaused)
                    {
                        return;
                    }

                    m_pauseState = PauseState(true, m_isLocationActive, m_isHeadingActive);

                    StopUpdating();
                }

                void SenionLabLocationServiceImpl::OnResume()
                {
                    if(!m_pauseState.isPaused)
                    {
                        return;
                    }

                    m_pauseState.isPaused = false;

                    if(m_pauseState.wasUpdatingLocation || m_pauseState.wasUpdatingHeading)
                    {
                        StartUpdating();
                    }
                }

                bool SenionLabLocationServiceImpl::IsLocationAuthorized() const
                {
                    return m_isAuthorized;
                }

                bool SenionLabLocationServiceImpl::IsLocationActive() const
                {
                    return m_isLocationActive;
                }

                bool SenionLabLocationServiceImpl::GetLocation(Eegeo::Space::LatLong &latlong) const
                {
                    latlong.SetLatitude(m_location.GetLatitude());
                    latlong.SetLongitude(m_location.GetLongitude());
                    return true;
                }

                bool SenionLabLocationServiceImpl::GetAltitude(double &altitude) const
                {
                    const auto* interiorModel = m_interiorInteractionModel.GetInteriorModel();

                    if(interiorModel == nullptr || m_wrldFloorIndex < 0)
                    {
                        return false;
                    }
                 
                    altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(
                            *interiorModel,
                            static_cast<unsigned int>(m_wrldFloorIndex),
                            m_environmentFlatteningService.GetCurrentScale());

                    return true;
                }

                bool SenionLabLocationServiceImpl::GetHorizontalAccuracy(double &accuracy) const
                {
                    accuracy = m_horizontalAccuracy;
                    return true;
                }

                void SenionLabLocationServiceImpl::StartUpdatingLocation()
                {
                    StartUpdating();
                }

                void SenionLabLocationServiceImpl::StopUpdatingLocation()
                {
                    m_isLocationActive = false;

                    // we only want to stop updating if both location & heading aren't required
                    if(!IsActive())
                    {
                        StopUpdating();
                    }
                }

                bool SenionLabLocationServiceImpl::GetHeadingDegrees(double &headingDegrees) const
                {
                    // todo loc: if senion is not configured to get heading...
                    if(m_isHeadingActive && m_isAuthorized)
                    {
                        headingDegrees = m_headingDegrees;
                        return true;
                    }
                    
                    return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
                }

                bool SenionLabLocationServiceImpl::IsHeadingAuthorized() const
                {
                    return m_isAuthorized;
                }

                bool SenionLabLocationServiceImpl::IsHeadingActive() const
                {
                    return m_isHeadingActive ? true : m_defaultLocationService.IsHeadingActive();
                }

                void SenionLabLocationServiceImpl::StartUpdatingHeading()
                {
                    StartUpdating();
                }

                void SenionLabLocationServiceImpl::StopUpdatingHeading()
                {
                    m_isHeadingActive = false;

                    // we only want to stop updating if both location & heading aren't required
                    if(IsActive())
                    {
                        StopUpdating();
                    }
                }

                bool SenionLabLocationServiceImpl::IsIndoors() const
                {
                    return true;
                }

                Eegeo::Resources::Interiors::InteriorId SenionLabLocationServiceImpl::GetInteriorId() const
                {
                    return m_interiorInteractionModel.HasInteriorModel() ?
                            m_interiorInteractionModel.GetInteriorModel()->GetId() :
                            Eegeo::Resources::Interiors::InteriorId::NullId();
                }

                bool SenionLabLocationServiceImpl::GetFloorIndex(int &floorIndex) const
                {
                    floorIndex = m_wrldFloorIndex;
                    return true;
                }

                bool SenionLabLocationServiceImpl::IsIndoorAuthorized() const
                {
                    return m_isAuthorized;
                }
            }
        }
    }
}
