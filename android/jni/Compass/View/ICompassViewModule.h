// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICompassView.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class ICompassViewModule
            {
            public:
                virtual ~ICompassViewModule() { }

                virtual ICompassView& GetCompassView() = 0;
            };
        }
    }
}
