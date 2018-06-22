// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IndoorAtlasIncludes.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                // seam between C++ and platform-dependent IndoorAtlas SDKs
                class IIndoorAtlasLocationInterop
                {
                public:
                    virtual ~IIndoorAtlasLocationInterop() {}
                
                    virtual void SetLocationService(IndoorAtlasLocationService* pLocationService) = 0;
                    
                    virtual void StartUpdating(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap) = 0;
                    
                    virtual void StopUpdating() = 0;
                };
            }
        }
    }
}
