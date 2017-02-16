// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <algorithm>

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                namespace
                {
                    std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> FilterSenionInteriorInfo(const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap)
                    {
                        typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;
                        TrackingInfoMap senionInfoMap;
                        const auto isSenionEntry([](const TrackingInfoMap::value_type& info)
                                                 { return info.second.GetType() == "Senion"; });
                        std::copy_if(trackingInfoMap.begin(),
                                     trackingInfoMap.end(),
                                     std::inserter(senionInfoMap, senionInfoMap.end()),
                                     isSenionEntry);
                        return senionInfoMap;
                    }
                }

                SenionLabLocationController::SenionLabLocationController(ISenionLabLocationManager& locationManager,
                                                                         ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                         const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap)
                : m_locationManager(locationManager)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_trackingInfoMap(FilterSenionInteriorInfo(trackingInfoMap))
                , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
                {
                    for (const auto& idAndEntry : m_trackingInfoMap)
                    {
                        const ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& interiorEntry = idAndEntry.second;
                        const std::string& mapKey = interiorEntry.GetConfig().GetApiKey();
                        m_floorMaps.insert(std::make_pair(mapKey, interiorEntry.GetFloorIndexMap()));
                        m_interiorIds.insert(std::make_pair(mapKey, interiorEntry.GetInteriorId()));
                    }

                    m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                SenionLabLocationController::~SenionLabLocationController()
                {
                    m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                void SenionLabLocationController::OnAppModeChanged()
                {
                    Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();

                    m_locationManager.StopUpdatingLocation();
                 
                    if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        if (!m_trackingInfoMap.empty())
                        {
                            const std::string& apiSecret(m_trackingInfoMap.begin()->second.GetConfig().GetApiSecret());
                            m_locationManager.StartUpdatingLocation(apiSecret,
                                                                    interiorId,
                                                                    m_trackingInfoMap,
                                                                    m_floorMaps,
                                                                    m_interiorIds);
                        }
                    }
                }
            }
        }
    }
}
