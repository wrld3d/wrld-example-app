// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IndoorLocation.h"

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            class IIndoorLocationModule
            {
            public:
                virtual ~IIndoorLocationModule() {}
                virtual IIndoorLocationDeviceModel& GetDeviceModel() const = 0;
            };
        }
    }
}