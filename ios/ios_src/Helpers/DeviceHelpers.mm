// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeviceHelpers.h"
#include <algorithm>

namespace ExampleApp
{
    namespace Helpers
    {
        int deviceFramerateBlacklist[] = {
            GAME_DEVICE_IPHONE1,
            GAME_DEVICE_IPHONE3G,
            GAME_DEVICE_IPHONE4,
            GAME_DEVICE_IPHONE4S,
            GAME_DEVICE_IPHONE5,
            GAME_DEVICE_IPOD1GEN,
            GAME_DEVICE_IPOD2GEN,
            GAME_DEVICE_IPOD3GEN,
            GAME_DEVICE_IPOD4GEN,
            GAME_DEVICE_IPOD5GEN,
            GAME_DEVICE_IPAD1,
            GAME_DEVICE_IPAD2,
            GAME_DEVICE_IPAD3,
            GAME_DEVICE_IPAD4,
            GAME_DEVICE_IPADAIR,
            GAME_DEVICE_IPADMINI_1GEN,
            GAME_DEVICE_IPADMINI_2
        };
        
        namespace DeviceHelpers
        {
            NSInteger GetPreferredFramerate(const GameDeviceType& deviceType)
            {   
                bool isBlacklisted = std::find(std::begin(deviceFramerateBlacklist), std::end(deviceFramerateBlacklist), deviceType) != std::end(deviceFramerateBlacklist);
                
                return isBlacklisted ? (NSInteger)30 : (NSInteger)60;
            }
        }
    }
}
