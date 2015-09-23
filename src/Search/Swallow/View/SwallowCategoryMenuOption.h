// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuOption.h"
#include "Menu.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace View
            {
                class SwallowCategoryMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
                {
                    std::string m_category;
                    Menu::View::IMenuViewModel& m_menuViewModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                public:
                    SwallowCategoryMenuOption(std::string category,
                                              Menu::View::IMenuViewModel& menuViewModel,
                                              ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~SwallowCategoryMenuOption();
                    
                    void Select();
                };
            }
        }
    }
}
