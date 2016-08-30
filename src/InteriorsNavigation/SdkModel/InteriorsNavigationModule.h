// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            class InteriorsNavigationModule
            {
            public:
                InteriorsNavigationModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
                
                void Register();
            private:
                const std::shared_ptr<Hypodermic::ContainerBuilder> m_builder;
            };
        }
    }
}
