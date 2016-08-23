// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "RestrictedBuildingInfo.h"



namespace ExampleApp
{
    namespace ApplicationConfig
    {
        RestrictedBuildingInfo::RestrictedBuildingInfo(const std::string interiorID,std::vector<std::string> allowedWifiIds): m_interiorID(interiorID), m_allowedWifiIds(allowedWifiIds)
        {
            
        }
        

        const std::vector<std::string>& RestrictedBuildingInfo::AllowedWifiIDs()const
        {
            return m_allowedWifiIds;
        }
        
        const std::string& RestrictedBuildingInfo::InteriorID() const
        {
            return m_interiorID;
        }
    }
}