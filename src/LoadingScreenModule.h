// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    class LoadingScreenModule : public Module
    {
    public:
        void Register(const TContainerBuilder& builder);
    };
}
