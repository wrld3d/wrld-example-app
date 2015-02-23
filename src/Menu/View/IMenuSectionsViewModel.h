// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuSectionsViewModel
            {
            public:
                virtual ~IMenuSectionsViewModel() {};

                virtual void AddSection(IMenuSectionViewModel& section) = 0;
                virtual void RemoveSection(IMenuSectionViewModel& section) = 0;

                virtual size_t SectionsCount() const = 0;
                virtual size_t NumberOfCells() const = 0;

                virtual IMenuSectionViewModel& GetMenuSection(int index) const = 0;
            };
        }
    }
}
