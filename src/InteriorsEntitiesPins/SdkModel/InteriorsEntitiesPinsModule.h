// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            class InteriorsEntitiesPinsModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
            };
        }
    }
}