// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class SearchMenuModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
        }
    }
}