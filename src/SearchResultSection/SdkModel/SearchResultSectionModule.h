// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultSectionModule : public Module
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
                void RegisterNativeLeaves();
                void RegisterUiLeaves();
            };
        }
    }
}
