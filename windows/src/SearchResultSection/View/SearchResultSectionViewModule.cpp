// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionViewModule.h"

#include "IMenuOptionsModel.h"
#include "IMenuViewModel.h"
#include "SearchResultSectionController.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            SearchResultSectionViewModule::SearchResultSectionViewModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                         Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                                         ISearchResultSectionOrder& searchResultSectionOrder,
                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                         const Menu::View::IMenuReactionModel& menuReaction,
                                                                         SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            {
                m_pController =  Eegeo_NEW(SearchResultSectionController)(searchMenuViewModel,
                                                                          menuOptionsModel,
                                                                          searchResultSectionOrder,
                                                                          messageBus,
                                                                          menuReaction,
                                                                          searchResultPoiViewModel);
            }

            SearchResultSectionViewModule::~SearchResultSectionViewModule()
            {
                Eegeo_DELETE m_pController;
            }
        }
    }
}
