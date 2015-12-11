// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuViewModule.h"

#include "IMenuOptionsModel.h"
#include "IMenuViewModel.h"
#include "SearchResultMenuController.h"
#include "SearchResultMenuDataProvider.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuViewModule::SearchResultMenuViewModule(CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                                                   Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                   Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                                   ISearchResultMenuOrder& searchResultMenuOrder,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [SearchResultMenuDataProvider alloc];
                
                m_pController =  Eegeo_NEW(SearchResultMenuController)(searchMenuViewModel,
                                                                       menuOptionsModel,
                                                                       searchResultMenuOrder,
                                                                       categorySearchRepository,
                                                                       messageBus);
            }

            SearchResultMenuViewModule::~SearchResultMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pDataProvider release];
            }
        }
    }
}
