// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace IpAddressHelpers
        {
            struct InterfaceInfo
            {
                std::string name;
                std::string ipVersion;
                std::string ipAddress;
            };
            
            std::vector<InterfaceInfo> GetActiveIpInterfaceInfos();
            
            std::string GetWifiIpAddress();
        }
    }
}