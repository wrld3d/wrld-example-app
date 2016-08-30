// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModule.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class SearchResultOnMapModule : public IModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
        }
    }
}
