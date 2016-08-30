// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
                void RegisterLeaves();
            };
        }
    }
}