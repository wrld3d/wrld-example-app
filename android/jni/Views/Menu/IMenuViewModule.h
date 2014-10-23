// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MenuViewIncludes.h"

namespace ExampleApp
{
    namespace Menu
    {
        class IMenuViewModule
        {
        public:
            virtual ~IMenuViewModule() { }
            
            virtual IMenuViewController& GetMenuViewController() const = 0;
        };
    }
}
