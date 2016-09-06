// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            class InteriorsNavigationModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
            };
        }
    }
}
