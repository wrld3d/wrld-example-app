// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "EnvironmentFlatteningService.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorHeightHelpers.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "IPSConfigurationParser.h"
#include "ILocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                // public api
                SenionLabLocationService::SenionLabLocationService(
                        ISenionLabLocationInterop& senionInterop,
                        Eegeo::Location::ILocationService& defaultLocationService,
                        ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                        const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                        const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_senionInterop(senionInterop)
                , m_defaultLocationService(defaultLocationService)
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
                    
                }

                SenionLabLocationService::~SenionLabLocationService()
                {
                    
                }

                bool SenionLabLocationService::IsActive() const
                {
                    return m_isHeadingActive || m_isLocationActive;
                }
                
                void SenionLabLocationService::SetIsAuthorized(bool isAuthorized)
                {
                    m_isAuthorized = isAuthorized;
                }

                // todo loc: this should possibly be moved to the app domain
                void SenionLabLocationService::PublishAboutPageSenionDataMessage()
                {
                    m_messageBus.Publish(ExampleApp::AboutPage::AboutPageSenionDataMessage(m_wrldFloorIndex, m_senionFloorNumber, m_location.GetLatitudeInDegrees(), m_location.GetLongitudeInDegrees()));
                }
                
                void SenionLabLocationService::SetLocationFromSenionData(const Eegeo::Space::LatLong &latLong,
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
                
                void SenionLabLocationService::SetHeadingFromSenionData(double headingDegrees, bool isAccurate)
                {
                    SetIsAuthorized(true);
                    
                    if(isAccurate) // todo loc: test this more; first stab
                    {
                        m_headingDegrees = headingDegrees;
                    }
                }
                
                // Non-interface methods
                void SenionLabLocationService::StartUpdating()
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
                    
                    m_senionInterop.StartUpdatingLocation(trackingInfo.GetConfig().GetApiKey(),
                                                          trackingInfo.GetConfig().GetApiSecret(),
                                                          trackingInfo.GetFloorIndexMap());
                    
                    m_defaultLocationService.StopUpdatingLocation();
                    
                    // todo: heading configuration -- only use heading if configured to do so
                    m_defaultLocationService.StopUpdatingHeading();
                    
                    m_isHeadingActive = true;
                    m_isLocationActive = true;
                }

                void SenionLabLocationService::StopUpdating()
                {
                    if(!IsActive())
                    {
                        return;
                    }
                    
                    m_isLocationActive = false;
                    m_isHeadingActive = false;
                    
                    m_senionInterop.StopUpdatingLocation();
                }
                
                void SenionLabLocationService::RestoreDefaultState()
                {
                    m_defaultLocationService.StartUpdatingLocation();
                    m_defaultLocationService.StartUpdatingHeading();
                }

                // General
                void SenionLabLocationService::OnPause()
                {
                    if(m_pauseState.isPaused)
                    {
                        return;
                    }
                    
                    m_pauseState = PauseState(true, m_isLocationActive, m_isHeadingActive);
                    
                    StopUpdating();
                }
                
                void SenionLabLocationService::OnResume()
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
                
                // Location
                bool SenionLabLocationService::IsLocationAuthorized() const
                {
                    return m_isAuthorized;
                }
                
                bool SenionLabLocationService::IsLocationActive() const
                {
                    return m_isLocationActive;
                }
                
                bool SenionLabLocationService::GetLocation(Eegeo::Space::LatLong &latlong) const
                {
                    latlong.SetLatitude(m_location.GetLatitude());
                    latlong.SetLongitude(m_location.GetLongitude());
                    return true;
                }
                
                bool SenionLabLocationService::GetAltitude(double &altitude) const
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

                
                bool SenionLabLocationService::GetHorizontalAccuracy(double& accuracy) const
                {
                    accuracy = m_horizontalAccuracy;
                    return true;
                }
                
                void SenionLabLocationService::StartUpdatingLocation()
                {
                    StartUpdating();
                }
                
                void SenionLabLocationService::StopUpdatingLocation()
                {
                    m_isLocationActive = false;
                    
                    // we only want to stop updating if both location & heading aren't required
                    if(!IsActive())
                    {
                        StopUpdating();
                    }
                }
                
                // Heading
                bool SenionLabLocationService::GetHeadingDegrees(double& headingDegrees) const
                {
                    // todo loc: if senion is not configured to get heading...
                    if(m_isHeadingActive && m_isAuthorized)
                    {
                        headingDegrees = m_headingDegrees;
                        return true;
                    }
                    
                    return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
                }
                
                bool SenionLabLocationService::IsHeadingAuthorized() const
                {
                    return m_isAuthorized;
                }
                
                bool SenionLabLocationService::IsHeadingActive() const
                {
                    return m_isHeadingActive ? true : m_defaultLocationService.IsHeadingActive();
                }
                
                void SenionLabLocationService::StartUpdatingHeading()
                {
                    StartUpdating();
                }
                
                void SenionLabLocationService::StopUpdatingHeading()
                {
                    m_isHeadingActive = false;
                    
                    // we only want to stop updating if both location & heading aren't required
                    if(IsActive())
                    {
                        StopUpdating();
                    }
                }
                
                // Indoor
                bool SenionLabLocationService::IsIndoors() const
                {
                    return true;
                }
                
                Eegeo::Resources::Interiors::InteriorId SenionLabLocationService::GetInteriorId() const
                {
                    return m_interiorInteractionModel.HasInteriorModel() ?
                        m_interiorInteractionModel.GetInteriorModel()->GetId() :
                        Eegeo::Resources::Interiors::InteriorId::NullId();
                }
                
                bool SenionLabLocationService::GetFloorIndex(int& floorIndex) const
                {
                    floorIndex = m_wrldFloorIndex;
                    return true;
                }
                
                bool SenionLabLocationService::IsIndoorAuthorized() const
                {
                    return m_isAuthorized;
                }
            }
        }
    }
}
