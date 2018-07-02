// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationService.h"
#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "InteriorHeightHelpers.h"
#include "IPSConfigurationParser.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                // public api
                IndoorAtlasLocationService::IndoorAtlasLocationService(IIndoorAtlasLocationInterop& indoorAtlasInterop,
                                                                       Eegeo::Location::ILocationService& defaultLocationService,
                                                                       ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                                                       const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                       const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                       const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                       const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_indoorAtlasInterop(indoorAtlasInterop)
                , m_defaultLocationService(defaultLocationService)
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
                    
                }

                IndoorAtlasLocationService::~IndoorAtlasLocationService()
                {
                    
                }
                
                // Non-interface methods
                void IndoorAtlasLocationService::SetIsAuthorized(bool isAuthorized)
                {
                    m_isAuthorized = isAuthorized;
                }
                
                void IndoorAtlasLocationService::SetIsActive(bool isActive)
                {
                    m_isActive = isActive;
                }
                
                void IndoorAtlasLocationService::SetLocation(const Eegeo::Space::LatLong &latLong)
                {
                    SetIsAuthorized(true);
                    m_latLong = latLong;
                    
                    PublishAboutPageIndoorAtlasDataMessage();
                }
                
                void IndoorAtlasLocationService::SetHorizontalAccuracy(double radius)
                {
                    m_horizontalAccuracy = radius;
                }
                
                void IndoorAtlasLocationService::SetFloor(const std::string& indoorAtlasFloorId, int floorIndex)
                {
                    m_indoorAtlasFloorId = indoorAtlasFloorId;
                    m_floorIndex = floorIndex;
                    
                    PublishAboutPageIndoorAtlasDataMessage();
                }
                
                void IndoorAtlasLocationService::RestoreDefaultState()
                {
                    m_defaultLocationService.StartUpdatingLocation();
                    m_defaultLocationService.StartUpdatingHeading();
                }
                
                void IndoorAtlasLocationService::PublishAboutPageIndoorAtlasDataMessage()
                {
                    m_messageBus.Publish(ExampleApp::AboutPage::AboutPageIndoorAtlasDataMessage(
                            m_floorIndex,
                            m_indoorAtlasFloorId,
                            m_latLong.GetLatitudeInDegrees(),
                            m_latLong.GetLongitudeInDegrees()));
                }

                void IndoorAtlasLocationService::StartUpdating()
                {
                    StartUpdatingLocation();
                    StartUpdatingHeading();
                }

                void IndoorAtlasLocationService::StopUpdating()
                {
                    StopUpdatingLocation();
                    StopUpdatingHeading();
                }

                // General
                void IndoorAtlasLocationService::OnPause()
                {
                    if(m_pauseState.isPaused)
                    {
                        return;
                    }
                    
                    m_pauseState = PauseState(true, m_isActive, m_isActive);
                    
                    StopUpdatingLocation();
                    StopUpdatingHeading();
                }

                void IndoorAtlasLocationService::OnResume()
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

                // Location
                bool IndoorAtlasLocationService::IsLocationAuthorized() const
                {
                    return m_isAuthorized;
                }

                bool IndoorAtlasLocationService::IsLocationActive() const
                {
                    return m_isActive;
                }

                bool IndoorAtlasLocationService::GetLocation(Eegeo::Space::LatLong& latLong) const
                {
                    latLong.SetLatitude(m_latLong.GetLatitude());
                    latLong.SetLongitude(m_latLong.GetLongitude());
                    return true;
                }

                bool IndoorAtlasLocationService::GetAltitude(double& altitude) const
                {
                    const auto* interiorModel = m_interiorInteractionModel.GetInteriorModel();
                    
                    if(interiorModel == nullptr || m_floorIndex < 0)
                    {
                        return false;
                    }

                    altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(*interiorModel,
                                                                                                                                     static_cast<unsigned int>(m_floorIndex),
                                                                                                                                     m_environmentFlatteningService.GetCurrentScale());
                    return true;
                }

                bool IndoorAtlasLocationService::GetHorizontalAccuracy(double& accuracy) const
                {
                    accuracy = m_horizontalAccuracy;
                    return true;
                }

                void IndoorAtlasLocationService::StartUpdatingLocation()
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
                    
                    m_indoorAtlasInterop.StartUpdating(trackingInfo.GetConfig().GetApiKey(),
                                                       trackingInfo.GetConfig().GetApiSecret(),
                                                       trackingInfo.GetFloorIndexMap());
                                                               
                    SetIsActive(true);
                }

                void IndoorAtlasLocationService::StopUpdatingLocation()
                {
                    if(!m_isActive)
                    {
                        return;
                    }
                    
                    m_indoorAtlasInterop.StopUpdating();
                    SetIsActive(false);
                }

                // Heading
                bool IndoorAtlasLocationService::GetHeadingDegrees(double& headingDegrees) const
                {
                    // indoor atlas just provides location; fall back to default for heading
                    return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
                }

                bool IndoorAtlasLocationService::IsHeadingAuthorized() const
                {
                    return m_isAuthorized;
                }

                bool IndoorAtlasLocationService::IsHeadingActive() const
                {
                    return m_isActive;
                }

                void IndoorAtlasLocationService::StartUpdatingHeading()
                {
                    if(m_defaultLocationService.IsHeadingActive())
                    {
                        return;
                    }
                    
                    m_defaultLocationService.StartUpdatingHeading();
                }

                void IndoorAtlasLocationService::StopUpdatingHeading()
                {
                    m_defaultLocationService.StopUpdatingHeading();
                }

                // Indoor
                bool IndoorAtlasLocationService::IsIndoors() const
                {
                    return true;
                }

                Eegeo::Resources::Interiors::InteriorId IndoorAtlasLocationService::GetInteriorId() const
                {
                    return m_interiorInteractionModel.HasInteriorModel() ?
                    m_interiorInteractionModel.GetInteriorModel()->GetId() :
                    Eegeo::Resources::Interiors::InteriorId::NullId();
                }

                bool IndoorAtlasLocationService::GetFloorIndex(int& floorIndex) const
                {
                    floorIndex = m_floorIndex;
                    return true;
                }

                bool IndoorAtlasLocationService::IsIndoorAuthorized() const
                {
                    return m_isAuthorized;
                }
            }
        }
    }
}
