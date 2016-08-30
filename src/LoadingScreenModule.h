// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IModule.h"

namespace ExampleApp
{
    class LoadingScreenModule : public IModule
    {
    public:
        void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
    };
}
