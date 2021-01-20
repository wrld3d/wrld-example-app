// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IPSConfigurationParser.h"
#include "AboutPageIndoorPositionSettingsMessage.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationController::SenionLabLocationController(ISenionLabLocationManager& locationManager,
                                                                         ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                         const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         const Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataService& interiorMetaDataService,
                                                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_locationManager(locationManager)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
                , m_interiorMetaDataService(interiorMetaDataService)
                , m_messageBus(messageBus)
                , m_updatingLocation(false)
                {
                    m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                SenionLabLocationController::~SenionLabLocationController()
                {
                    m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                void SenionLabLocationController::OnAppModeChanged()
                {
                    typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;

                    const Eegeo::Resources::Interiors::InteriorId& interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    TrackingInfoMap trackingInfoMap;
                    
                    if(interiorId.IsValid())
                    {
                        InteriorsPosition::TryAndGetInteriorTrackingInfo(trackingInfoMap, interiorId, m_interiorMetaDataService);
                    }
                    else
                    {
                        return;
                    }

                    if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        const TrackingInfoMap::const_iterator trackingInfoEntry = trackingInfoMap.find(interiorId.Value());

                        if (trackingInfoEntry != trackingInfoMap.end())
                        {
                            const ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = trackingInfoEntry->second;

                            if (!m_updatingLocation && trackingInfo.GetType() == "Senion")
                            {
                                const std::string& apiKey = trackingInfo.GetConfig().GetApiKey();
                                const std::string& apiSecret = trackingInfo.GetConfig().GetApiSecret();
                                const std::map<int, std::string>& floorMap = trackingInfo.GetFloorIndexMap();

                                m_messageBus.Publish(AboutPage::AboutPageIndoorPositionSettingsMessage(
                                        apiKey,
                                        apiSecret,
                                        floorMap,
                                        trackingInfo.GetInteriorId().Value()));

                                StartUpdatingLocation(apiKey, apiSecret, floorMap);
                            }
                        }
                    }
                }

                void SenionLabLocationController::StartUpdatingLocation(const std::string& apikey, const std::string& apiSecret, const std::map<int, std::string>& floorMap)
                {
                    m_locationManager.StartUpdatingLocation(apikey, apiSecret, floorMap);
                    m_updatingLocation = true;
                }

                void SenionLabLocationController::StopUpdatingLocation()
                {
                    m_locationManager.StopUpdatingLocation();
                    m_updatingLocation = false;
                }
            }
        }
    }
}
