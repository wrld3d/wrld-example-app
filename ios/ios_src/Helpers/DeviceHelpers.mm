// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeviceHelpers.h"
#include <algorithm>

namespace ExampleApp
{
    namespace Helpers
    {
        int deviceFramerateWhitelist[] = {
            GAME_DEVICE_IPHONE8_PLUS,
            GAME_DEVICE_IPHONE8,
            GAME_DEVICE_IPADPRO_12_9_INCH,
            GAME_DEVICE_IPADPRO_9_7_INCH,
            GAME_DEVICE_IPHONE_SE,
            GAME_DEVICE_IPHONE7_PLUS,
            GAME_DEVICE_IPHONE7,
            GAME_DEVICE_IPHONE6S_PLUS,
            GAME_DEVICE_IPHONE6S,
            GAME_DEVICE_IPHONE6PLUS,
            GAME_DEVICE_IPHONE6,
            GAME_DEVICE_IPHONE5S,
            GAME_DEVICE_IPOD6GEN,
            GAME_DEVICE_IPADAIR_2,
            GAME_DEVICE_IPADMINI_3,
            GAME_DEVICE_IPADMINI_4
        };
        
        namespace DeviceHelpers
        {
            NSInteger GetPreferredFramerate(const GameDeviceType& deviceType)
            {   
                bool isWhitelisted = std::find(std::begin(deviceFramerateWhitelist), std::end(deviceFramerateWhitelist), deviceType) != std::end(deviceFramerateWhitelist);
                
                return isWhitelisted ? (NSInteger)60 : (NSInteger)30;
            }
        }
    }
}
