// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModule.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherMenuModule : public IModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
        }
    }
}
