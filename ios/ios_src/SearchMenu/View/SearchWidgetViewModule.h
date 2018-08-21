// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "SearchWidgetView.h"
#include "SearchWidgetController.h"
#include "SearchServices.h"
#include "IMenuViewModel.h"
#include "Modality.h"
#include "ISearchWidgetViewModule.h"
#include "SearchServices.h"
#include "SearchProvider.h"
#include "WidgetSearchProvider.h"
#include "SearchWidgetController.h"
#include "SearchWidgetContainerView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetViewModule:public ISearchWidgetViewModule, private Eegeo::NonCopyable
            {
            private:
                WidgetSearchProvider* m_pWrldSearchProvider;
                SearchWidgetController* m_pSearchWidgetController;
                SearchWidgetContainerView* m_pView;
                
                ISearchResultsRepository* m_pSearchResults;
                ISearchResultsRepository* m_pSuggestions;

                SearchMenu::View::SearchServices* m_pSearchServices;
                SearchProviders::SearchProvider* m_pSearchProvider;
                
                WRLDSearchModel* m_pSearchModel;
                
                QueryEvent m_autocompleteCancelledEvent;
            public:
                SearchWidgetViewModule(
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       Menu::View::IMenuViewModel& viewModel,
                                       bool isNavigationEnabled,
                                       ExampleAppMessaging::TMessageBus& messageBus
                                       );
                
                ~SearchWidgetViewModule();
                
                SearchWidgetContainerView& GetSearchWidgetView() const;
                SearchWidgetController& GetSearchWidgetController() const;
                ISearchResultsRepository& GetSuggestionsRepository() const;
                ISearchResultsRepository& GetSearchResultsRepository() const;
                WidgetSearchProvider* GetSuggestionProvider() const;

            };
        }
    }
}
