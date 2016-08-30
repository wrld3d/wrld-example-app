// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    class WorldModule : public Module
    {
    public:
        void Register(const TContainerBuilder& builder);
    };
}
