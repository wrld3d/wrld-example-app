// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Menu.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuOptionsModel
            {
            public:
                virtual ~IMenuOptionsModel() { }

                virtual void AddItem(const std::string& uniqueIdentifier,
                                     const std::string& name,
                                     const std::string& details,
                                     const std::string& icon,
                                     IMenuOption* pOption) = 0;

                virtual void RemoveItem(const std::string& uniqueIdentifier) = 0;
            };
        }
    }
}
