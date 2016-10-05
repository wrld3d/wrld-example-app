// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class NetworkModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterNativeLeaves();
            };
        }
    }
}
