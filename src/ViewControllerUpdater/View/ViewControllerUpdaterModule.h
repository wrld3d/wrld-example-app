// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IModule.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class ViewControllerUpdaterModule : public IModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
        }
    }
}
