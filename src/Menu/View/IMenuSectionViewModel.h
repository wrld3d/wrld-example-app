// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuSectionViewModel
            {
            public:

                virtual ~IMenuSectionViewModel() {};
                
                virtual IMenuModel& GetModel() const = 0;

                virtual const std::string& Name() const = 0;

                virtual const std::string& Icon() const = 0;

                virtual std::string SerializeJson() const = 0;

                virtual size_t Size() const = 0;

                virtual size_t GetTotalItemCount() const = 0;

                virtual MenuItemModel GetItemAtIndex(int index) const = 0;

                virtual bool IsExpanded() const = 0;
                
                virtual bool IsExpandable() const = 0;
                
                virtual bool IsSearchResult() const = 0;

                virtual void Expand() = 0;
                virtual void Contract() = 0;
            };
        }
    }
}
