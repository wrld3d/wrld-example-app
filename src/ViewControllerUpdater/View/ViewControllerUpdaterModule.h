// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Module.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class ViewControllerUpdaterModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterNativeLeaves();
            };
        }
    }
}
