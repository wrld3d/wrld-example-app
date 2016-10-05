// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

#include "Module.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterUiLeaves();
                void RegisterOpenablesAndReactors();
            };
        }
    }
}
