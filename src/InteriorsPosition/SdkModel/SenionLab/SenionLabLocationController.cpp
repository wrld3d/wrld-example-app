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
                                                                         const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap)
                : m_locationManager(locationManager)
                , m_trackingInfoMap(FilterSenionInteriorInfo(trackingInfoMap))
                {
                    for (const auto& idAndEntry : m_trackingInfoMap)
                    {
                        const ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& interiorEntry = idAndEntry.second;
                        const std::string& mapKey = interiorEntry.GetConfig().GetApiKey();
                        m_floorMaps.insert(std::make_pair(mapKey, interiorEntry.GetFloorIndexMap()));
                        m_interiorIds.insert(std::make_pair(mapKey, interiorEntry.GetInteriorId()));
                    }
                }
                
                SenionLabLocationController::~SenionLabLocationController()
                {
                }
                
                void SenionLabLocationController::StartUpdatingLocation()
                {
                    if (!m_trackingInfoMap.empty())
                    {
                        const std::string& apiSecret(m_trackingInfoMap.begin()->second.GetConfig().GetApiSecret());
                        m_locationManager.StartUpdatingLocation(apiSecret,
                                                                m_trackingInfoMap,
                                                                m_floorMaps,
                                                                m_interiorIds);
                    }
                }
                
                void SenionLabLocationController::StopUpdatingLocation()
                {
                    m_locationManager.StopUpdatingLocation();
                }
            }
        }
    }
}
