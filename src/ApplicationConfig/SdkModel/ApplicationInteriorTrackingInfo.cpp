// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "ApplicationInteriorTrackingInfo.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationInteriorTrackingInfo::ApplicationInteriorTrackingInfo(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                             const std::string& type,
                                                                             const ApplicationInteriorTrackingConfig& config,
                                                                             const std::map<int, std::string>& floorIndexMap)
            : m_interiorId(interiorId)
            , m_type(type)
            , m_config(config)
            , m_floorIndexMap(floorIndexMap)
            {
            }
            
            ApplicationInteriorTrackingInfo::~ApplicationInteriorTrackingInfo()
            {
            }
            
            const Eegeo::Resources::Interiors::InteriorId& ApplicationInteriorTrackingInfo::GetInteriorId() const
            {
                return m_interiorId;
            }
            
            const std::string& ApplicationInteriorTrackingInfo::GetType() const
            {
                return m_type;
            }
            
            const ApplicationInteriorTrackingConfig& ApplicationInteriorTrackingInfo::GetConfig() const
            {
                return m_config;
            }
            
            const std::map<int, std::string>& ApplicationInteriorTrackingInfo::GetFloorIndexMap() const
            {
                return m_floorIndexMap;
            }
        }
    }
}
