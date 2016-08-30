// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class MapModeModule
            {
            public:
                MapModeModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
                
                void Register();
            private:
                const std::shared_ptr<Hypodermic::ContainerBuilder> m_builder;
            };
        }
    }
}