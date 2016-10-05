// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkViewModule: public Module
            {
            public:
            	void Register(const TContainerBuilder& builder);
            	void RegisterLeaves();
            };
        }
    }
}
