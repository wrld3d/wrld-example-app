// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuViewModule.h"
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "SearchResultMenuView.h"
#include "ScreenProperties.h"
#include "MenuView.h"
#include "MenuController.h"
#include "SearchResultMenuController.h"
#include "SearchResultMenuViewInterop.h"
#include "MenuViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuViewModule::SearchResultMenuViewModule(CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                    Menu::View::IMenuModel& searchResultMenuModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ISearchResultMenuViewModel& searchResultMenuViewModel,
                    Menu::View::IMenuOptionsModel& menuOptionsModel,
                    ISearchResultMenuOrder& searchResultMenuOrder,
                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [SearchResultMenuDataProvider alloc];

                m_pView = [[SearchResultMenuView alloc]  initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :false
                           :menuViewModel.SectionsCount()
                           :menuViewModel.NumberOfCells()
                           :m_pDataProvider];

                m_pController =  Eegeo_NEW(SearchResultMenuController)(*[m_pView getSearchInterop],
                                 *[m_pView getInterop],
                                 searchResultMenuModel,
                                 menuViewModel,
                                 menuOptionsModel,
                                 searchResultMenuOrder,
                                 categorySearchRepository,
                                 searchResultMenuViewModel,
                                 messageBus
                                                                      );

            }

            SearchResultMenuViewModule::~SearchResultMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
                [m_pDataProvider release];
            }

            Menu::View::MenuController& SearchResultMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            SearchResultMenuView& SearchResultMenuViewModule::GetSearchResultMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
