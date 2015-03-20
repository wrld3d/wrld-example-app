// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class SortedMenuModel : public Menu::View::MenuModel
            {
                typedef Menu::View::MenuItemModel TModel;
                typedef bool (*TComparer)(const TModel& a, const TModel& b);
                
                TComparer m_comparer;
                
            public:
                SortedMenuModel(TComparer comparer);
                
                void AddItem(const TModel& item);
            };
        }
    }
}
