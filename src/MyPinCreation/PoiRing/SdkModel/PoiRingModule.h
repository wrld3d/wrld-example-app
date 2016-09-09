// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingModule : public Module
                {
                public:
                    void Register(const TContainerBuilder& builder);
                    void RegisterRenderableFilters();
                };
            }
        }
    }
}
