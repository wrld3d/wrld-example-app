// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldAreaLoader.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            class IWorldAreaLoaderModule
            {
            public:
                virtual ~IWorldAreaLoaderModule() { }

                virtual IWorldAreaLoaderModel& GetWorldAreaLoaderModel() const = 0;
            };
        }
    }
}
