// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class SearchMenuModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterNativeLeaves();
                void RegisterOpenablesAndReactors();
            };
        }
    }
}