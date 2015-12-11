// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewModule.h"

#include "MenuViewInterop.h"
#include "ScreenProperties.h"
#include "SearchMenuView.h"
#include "SearchMenuViewInterop.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuViewModule::SearchMenuViewModule(Menu::View::IMenuModel& searchMenuModel,
                                                       Menu::View::IMenuViewModel& searchMenuViewModel,
                                                       const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [CustomTableDataProvider alloc];

                m_pView = [[SearchMenuView alloc] initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :false
                           :searchMenuViewModel.SectionsCount()
                           :searchMenuViewModel.NumberOfCells()
                           :m_pDataProvider];

                m_pController = Eegeo_NEW(SearchMenuController)(searchMenuModel,
                                                                searchMenuViewModel,
                                                                *[m_pView getInterop],
                                                                *[m_pView getSearchMenuInterop],
                                                                messageBus);
            }

            SearchMenuViewModule::~SearchMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
                
                [m_pDataProvider release];
            }

            Menu::View::MenuController& SearchMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            SearchMenuView& SearchMenuViewModule::GetSearchMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
