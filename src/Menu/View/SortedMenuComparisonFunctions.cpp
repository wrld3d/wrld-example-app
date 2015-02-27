// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SortedMenuComparisonFunctions.h"
#include "MenuItemModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            bool LexicographicalNameCompare(const Menu::View::MenuItemModel& a, const Menu::View::MenuItemModel& b)
            {
                return a.Name() < b.Name();
            }
        }
    }
}
