// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewModule.h"

#include "MenuViewInterop.h"
#include "ScreenProperties.h"
#include "SearchMenuView.h"
#include "SearchMenuViewInterop.h"
#include "SearchProvider.h"
#include "WidgetSearchProvider.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuViewModule::SearchMenuViewModule(Menu::View::IMenuModel& searchMenuModel,
                                                       Menu::View::IMenuViewModel& searchMenuViewModel,
                                                       Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                       const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                       TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [CustomTableDataProvider alloc];
                
                m_pSearchResultsDataProvider = [SearchResultsTableDataProvider alloc];

                m_pView = [[SearchMenuView alloc] initWithParams:screenProperties.GetScreenWidth()
                                                                :screenProperties.GetScreenHeight()
                                                                :screenProperties.GetPixelScale()
                                                                :m_pDataProvider
                                                                :static_cast<int>(searchMenuViewModel.SectionsCount())
                                                                :m_pSearchResultsDataProvider];

                m_pController = Eegeo_NEW(SearchMenuController)(searchMenuModel,
                                                                searchMenuViewModel,
                                                                *[m_pView getInterop],
                                                                *[m_pView getSearchMenuInterop],
                                                                searchSectionViewModel,
                                                                tagSearchRepository,
                                                                modalBackgroundView,
                                                                messageBus);
                
                m_pSearchProvider = Eegeo_NEW(SearchProviders::SearchProvider)();
                
                m_pWrldSearchProvider = [[WidgetSearchProvider alloc] initWithSearchProvider: m_pSearchProvider];
                
                m_pSearchWidgetView = Eegeo_NEW(SearchWidgetView)(m_pView,
                                                                  m_pWrldSearchProvider,
                                                                  m_pWrldSearchProvider);
                
                m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(*m_pSearchProvider,
                                                                                messageBus);
                
                m_pMenuSectionsViewModel = Eegeo_NEW(Menu::View::MenuSectionsViewModel)();
                
                m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(*m_pSearchWidgetView,
                                                                              *m_pSearchServices,
                                                                              *m_pMenuSectionsViewModel,
                                                                              messageBus);
            }

            SearchMenuViewModule::~SearchMenuViewModule()
            {
                Eegeo_DELETE m_pSearchWidgetController;
                
                Eegeo_DELETE m_pMenuSectionsViewModel;
                
                Eegeo_DELETE m_pSearchServices;
                
                Eegeo_DELETE m_pSearchWidgetView;
                
                Eegeo_DELETE m_pSearchProvider;
                
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

            SearchWidgetView& SearchMenuViewModule::GetSearchWidgetView() const
            {
                return *m_pSearchWidgetView;
            }
        }
    }
}
