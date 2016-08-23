// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class RestrictedBuildingInfo
        {
        
        private:
            const std::string m_interiorID;
            const std::vector<std::string> m_allowedWifiIds;

            
        public:
            RestrictedBuildingInfo(const std::string interiorID,std::vector<std::string> allowedWifiIds);
                        

            const std::string& InteriorID() const;
            const std::vector<std::string>& AllowedWifiIDs()const;
        
        };
    }
}