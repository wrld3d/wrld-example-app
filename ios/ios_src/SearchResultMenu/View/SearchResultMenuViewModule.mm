// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuViewModule.h"

#include "IMenuOptionsModel.h"
#include "IMenuViewModel.h"
#include "SearchResultMenuController.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuViewModule::SearchResultMenuViewModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                   Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                                   ISearchResultMenuOrder& searchResultMenuOrder,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pController =  Eegeo_NEW(SearchResultMenuController)(searchMenuViewModel,
                                                                       menuOptionsModel,
                                                                       searchResultMenuOrder,
                                                                       messageBus);
            }

            SearchResultMenuViewModule::~SearchResultMenuViewModule()
            {
                Eegeo_DELETE m_pController;
            }
        }
    }
}
