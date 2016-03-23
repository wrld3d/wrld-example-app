// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuOption.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "AppModes.h"
#include "ICallback.h"

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
                    bool m_inInteriorMode;
                    bool m_closeMenuInInterior;
                    float m_radiusOverride;
                    Menu::View::IMenuViewModel& m_menuViewModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    Eegeo::Helpers::TCallback1<SwallowCategoryMenuOption, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                    
                    void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);
                public:
                    SwallowCategoryMenuOption(std::string category,
                                              bool forceInteriorQuery,
                                              bool closeMenuWhenInInterior,
                                              Menu::View::IMenuViewModel& menuViewModel,
                                              ExampleAppMessaging::TMessageBus& messageBus);

                    SwallowCategoryMenuOption(std::string category,
                                              bool forceInteriorQuery,
                                              bool closeMenuWhenInInterior,
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
