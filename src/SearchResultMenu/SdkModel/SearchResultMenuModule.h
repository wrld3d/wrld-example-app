// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultMenuModule.h"

#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "Search.h"
#include "SearchResultMenuItemSelectedMessageHandler.h"
#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultViewClearedObserver.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            class SearchResultMenuModule: public ISearchResultMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                View::SearchResultRepositoryObserver* m_pSearchResultRepositoryObserver;
                View::SearchResultMenuSearchQueryRemovedMessageHandler* m_pSearchQueryRemovedMessageHandler;
                SearchResultMenuItemSelectedMessageHandler* m_pSearchResultMenuItemSelectedMessageHandler;
                SearchResultViewClearedObserver* m_pSearchResultViewClearedObserver;
                View::ISearchResultMenuOrder* m_pSearchResultMenuOrder;

            public:
                SearchResultMenuModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                       Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                       Search::SdkModel::ISearchQueryPerformer& queryPerformer,
                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuModule();

                Menu::View::IMenuOptionsModel& GetSearchResultMenuOptionsModel() const;

                Menu::View::IMenuModel& GetSearchResultMenuModel() const;
                
                View::ISearchResultMenuOrder& GetSearchResultMenuOrder() const;
            };
        }
    }
}
