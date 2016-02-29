// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuViewModule.h"
#include "SettingsMenuView.h"
#include "ScreenProperties.h"
#include "MenuViewInterop.h"
#include "SettingsMenuViewInterop.h"
#include "SettingsMenuController.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuViewModule::SettingsMenuViewModule(Menu::View::IMenuModel& settingsMenuModel,
                                                           Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [SettingsTableDataProvider alloc];

                m_pView = [[SettingsMenuView alloc] initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :m_pDataProvider
                           :static_cast<int>(settingsMenuViewModel.SectionsCount())];

                m_pController = Eegeo_NEW(SettingsMenuController)(*[m_pView getInterop],
                                                                  settingsMenuModel,
                                                                  settingsMenuViewModel,
                                                                  modalBackgroundView,
                                                                  messageBus);
            }

            SettingsMenuViewModule::~SettingsMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
                
                [m_pDataProvider release];
            }

            Menu::View::MenuController& SettingsMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            SettingsMenuView& SettingsMenuViewModule::GetSettingsMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
