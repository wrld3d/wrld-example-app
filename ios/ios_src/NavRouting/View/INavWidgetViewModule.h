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
                virtual ~INavWidgetViewModule() {}
                
                virtual UIView& GetNavWidgetView() const = 0;
                virtual NavWidgetController& GetNavWidgetController() const = 0;
            };
        }
    }
}
