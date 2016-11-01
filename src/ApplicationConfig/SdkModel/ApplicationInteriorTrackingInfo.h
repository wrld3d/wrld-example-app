// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ApplicationInteriorTrackingConfig.h"
#include "InteriorId.h"
#include <map>
#include <vector>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationInteriorTrackingInfo
            {
            public:
                ApplicationInteriorTrackingInfo(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                const std::string& type,
                                                const ApplicationInteriorTrackingConfig& config,
                                                const std::map<int, std::string>& floorIndexMap);
                ~ApplicationInteriorTrackingInfo();
                
                const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const;
                const std::string& GetType() const;
                const ApplicationInteriorTrackingConfig& GetConfig() const;
                const std::map<int, std::string>& GetFloorIndexMap() const;
                
            private:
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                std::string m_type;
                ApplicationInteriorTrackingConfig m_config;
                std::map<int, std::string> m_floorIndexMap;
            };
        }
    }
}
