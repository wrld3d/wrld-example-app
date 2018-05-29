// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavWidgetViewIncludes.h"
#include "NavWidgetController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetViewModule
            {
            public:
                virtual ~INavWidgetViewModule() { }

                virtual INavWidgetView& GetView() const = 0;
                virtual NavWidgetController& GetController() const = 0;
            };
        }
    }
}
