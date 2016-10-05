// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterNativeLeaves();
                void RegisterUiLeaves();
            };
        }
    }
}
