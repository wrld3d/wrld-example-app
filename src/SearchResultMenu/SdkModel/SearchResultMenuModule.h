// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "SearchResultMenu.h"
#include "ISearchResultMenuModule.h"
#include "IIdentity.h"
#include "CameraTransitions.h"
#include "Reaction.h"
#include "SearchResultMenuViewModel.h"
#include "SearchResultMenuItemSelectedMessageHandler.h"
#include "BidirectionalBus.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultMenuSearchQueryPerformedMessageHandler.h"
#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"
#include "SearchResultMenuAppModeMessageHandler.h"
#include "SearchResultViewClearedObserver.h"

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
                View::SearchResultMenuViewModel* m_pViewModel;
                View::SearchResultRepositoryObserver* m_pSearchResultRepositoryObserver;
                Menu::View::IMenuSectionViewModel* m_pMenuSection;
                SearchResultMenuItemSelectedMessageHandler* m_pSearchResultMenuItemSelectedMessageHandler;
                View::SearchResultMenuSearchQueryPerformedMessageHandler* m_pSearchResultMenuSearchQueryPerformedMessageHandler;
                View::SearchResultMenuSearchQueryRemovedMessageHandler* m_pSearchResultMenuSearchQueryRemovedMessageHandler;
                View::SearchResultMenuAppModeMessageHandler* m_pSearchResultMenuAppModeMessageHandler;
                SearchResultViewClearedObserver* m_pSearchResultViewClearedObserver;
                View::ISearchResultMenuOrder* m_pSearchResultMenuOrder;

            public:
                SearchResultMenuModule(
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    Search::SdkModel::ISearchQueryPerformer& queryPerformer,
                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SearchResultMenuModule();

                Menu::View::IMenuOptionsModel& GetSearchResultMenuOptionsModel() const;

                Menu::View::IMenuModel& GetSearchResultMenuModel() const;

                Menu::View::IMenuViewModel& GetMenuViewModel() const;

                View::ISearchResultMenuViewModel& GetSearchResultMenuViewModel() const;
                
                View::ISearchResultMenuOrder& GetSearchResultMenuOrder() const;
            };
        }
    }
}
