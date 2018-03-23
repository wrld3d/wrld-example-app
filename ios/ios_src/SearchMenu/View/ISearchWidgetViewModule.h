#pragma once

#include "SearchWidgetView.h"
#include "SearchWidgetController.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchWidgetViewModule
            {
            public:
                virtual ~ISearchWidgetViewModule() { }
                
                virtual SearchWidgetView& GetSearchWidgetView() const = 0;
                
                virtual SearchWidgetController& GetSearchWidgetController() const = 0;
            };
        }
    }
}

