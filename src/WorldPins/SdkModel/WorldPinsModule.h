// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterLeaves();
            };
        }
    }
}
