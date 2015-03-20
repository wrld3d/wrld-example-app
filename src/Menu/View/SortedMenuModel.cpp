// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <algorithm>
#include "SortedMenuModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            SortedMenuModel::SortedMenuModel(TComparer comparer)
            :m_comparer(comparer)
            {
                
            }
            
            void SortedMenuModel::AddItem(const TModel& item)
            {
                // The data model & encapsulation backing the menu, repository & underlying ObservableVector
                // prevent mutation outside of an abstract AddItem(T) and RemoveItem(T) interface, which generally
                // works well but prevents us from sorting directly in this case. Instead, we copy the data out
                // into a vector, sort it, and reinsert it into the menu storage. This is somewhat clumsy and will
                // cause observers to trigger, but this shouldn't result in problems (as observers should always be
                // able to accept events).
                
                std::vector<TModel> data;
                
                // Add all menu contents including new item to vector.
                for(size_t i = 0; i < GetItemCount(); ++ i)
                {
                    data.push_back(GetItemAtIndex(i));
                }
                data.push_back(item);
                
                // Remove all items from menu.
                while(GetItemCount() != 0)
                {
                    RemoveItem(GetItemAtIndex(0));
                }
                
                // Sort menu contents (including new item).
                std::sort(data.begin(), data.end(), m_comparer);
                
                // Add the items back to the menu. Result should be menu with single added item in sorted state.
                for(size_t i = 0; i < data.size(); ++ i)
                {
                    Menu::View::MenuModel::AddItem(data[i]);
                }
            }
        }
    }
}
