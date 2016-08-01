// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IpAddressHelpers.h"

extern "C"
{
#ifndef EEGEO_WIN
#include <arpa/inet.h>  
#include <net/if.h>
#include "EegeoPlatformMacros.h"

#endif
// If using this on android it need and implementation available in GitHub with name android-ifaddrs
// android-ifaddrs include must come after net/if.h
#if !defined(EEGEO_DROID) && !defined(EEGEO_WIN)
#include <ifaddrs.h>
#endif
    
}

#include <vector>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace IpAddressHelpers
        {
            namespace
            {
                bool Contains(const std::string& string, const std::string& searchFor)
                {
                    return string.find(searchFor) != std::string::npos;
                }
            }
            
            // May be better off with platform specific implementations of this
            std::vector<InterfaceInfo> GetActiveIpInterfaceInfos()
            {
                
                std::vector<InterfaceInfo> interfaceInfos;
#if !defined(EEGEO_DROID) && !defined (EEGEO_WIN)
                struct ifaddrs *interfaceList;
                
                if(!getifaddrs(&interfaceList))
                {
                    // Loop through linked list of interfaces
                    struct ifaddrs *interface;
                    for(interface=interfaceList; interface != NULL; interface=interface->ifa_next)
                    {
                        if(!(interface->ifa_flags & IFF_UP) || (interface->ifa_flags & IFF_LOOPBACK))
                        {
                            continue;
                        }
                        
                        InterfaceInfo interfaceInfo;
                        interfaceInfo.name = interface->ifa_name;
                        
                        const struct sockaddr_in *addr = (const struct sockaddr_in*)interface->ifa_addr;
                        
                        if(addr && (addr->sin_family==AF_INET || addr->sin_family==AF_INET6))
                        {
                            char addrBuf[INET6_ADDRSTRLEN];
                            
                            
                            if(inet_ntop(addr->sin_family, &addr->sin_addr, addrBuf, INET6_ADDRSTRLEN))
                            {
                                if(addr->sin_family == AF_INET)
                                {
                                    interfaceInfo.ipVersion = "ipv4";
                                }
                                else
                                {
                                    interfaceInfo.ipVersion = "ipv6";
                                }
                                interfaceInfo.ipAddress = addrBuf;
                                interfaceInfos.push_back(interfaceInfo);
                            }
                        }
                    }
                    // Free memory
                    freeifaddrs(interfaceList);
                }
#endif                
                return interfaceInfos;
            }
            
            std::string GetWifiIpAddress()
            {
                std::string wifiAddress("");
                std::vector<InterfaceInfo> interfaceInfos = GetActiveIpInterfaceInfos();
                for(int i = 0; i < interfaceInfos.size(); ++i)
                {
                    if(Contains(interfaceInfos[i].name, "en") ||
                       Contains(interfaceInfos[i].name, "wifi") ||
                       Contains(interfaceInfos[i].name, "wlan")
                       )
                    {
                        // Prefer ipv4 address as ipv6 doesn't seem to be returned correctly from inet_ntop (at least for ipv4 connection on same interface)
                        if(interfaceInfos[i].ipVersion == "ipv4")
                        {
                            return interfaceInfos[i].ipAddress;
                        }
                        else
                        {
                            wifiAddress = interfaceInfos[i].ipAddress;
                        }
                    }
                }
                return wifiAddress;
            }
        }
    }
}
