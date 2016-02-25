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
                    bool m_hasRadiusOverride;
                    bool m_interior;
                    float m_radiusOverride;
                    Menu::View::IMenuViewModel& m_menuViewModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                public:
                    SwallowCategoryMenuOption(std::string category,
                                              bool forceInteriorQuery,
                                              Menu::View::IMenuViewModel& menuViewModel,
                                              ExampleAppMessaging::TMessageBus& messageBus);

                    SwallowCategoryMenuOption(std::string category,
                                              bool forceInteriorQuery,
                                              Menu::View::IMenuViewModel& menuViewModel,
                                              float radius,
                                              ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~SwallowCategoryMenuOption();
                    
                    void Select();
                };
            }
        }
    }
}
