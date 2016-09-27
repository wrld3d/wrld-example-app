// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuViewModule.h"

#include "MenuViewInterop.h"
#include "ScreenProperties.h"
#include "DirectionsMenuView.h"
#include "DirectionsMenuViewInterop.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            DirectionsMenuViewModule::DirectionsMenuViewModule(Menu::View::IMenuModel& searchMenuModel,
                                     Menu::View::IMenuViewModel& searchMenuViewModel,
                                    Menu::View::IMenuSectionViewModel& searchSectionViewModel,                                                               
                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                     ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pView = [[DirectionsMenuView alloc] initWithParams:screenProperties.GetScreenWidth()
                                                                :screenProperties.GetScreenHeight()
                                                                :screenProperties.GetPixelScale()];

                m_pController = Eegeo_NEW(DirectionsMenuController)(searchMenuModel,
                                                                searchMenuViewModel,
                                                                *[m_pView getInterop],
                                                                *[m_pView getDirectionsMenuInterop],
                                                                    searchSectionViewModel,
                                                                modalBackgroundView,
                                                                messageBus);
                
                
            }

            DirectionsMenuViewModule::~DirectionsMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
            }

            Menu::View::MenuController& DirectionsMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            DirectionsMenuView& DirectionsMenuViewModule::GetDirectionsMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
