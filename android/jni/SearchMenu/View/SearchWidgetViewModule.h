// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "SearchWidgetView.h"
#include "SearchWidgetController.h"
#include "MyTestSearchProvider.h"
#include "SearchServices.h"
#include "IMenuSectionsViewModel.h"
#include "Modality.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchWidgetViewModule: private Eegeo::NonCopyable
			{
			private:
				SearchWidgetView* m_pSearchWidgetView;
				SearchWidgetController* m_pSearchWidgetController;

				SearchProviders::MyTestSearchProvider* m_pMyTestSearchProvider;
				ISearchResultsRepository* m_pSearchResults;
				ISearchResultsRepository* m_pSuggestions;
				SearchServices* m_pSearchServices;

			public:
				SearchWidgetViewModule(
					AndroidNativeState& nativeState,
					Modality::View::IModalBackgroundView& modalBackgroundView,
					Menu::View::IMenuViewModel& viewModel,
					bool showNavigationButtons,
					ExampleAppMessaging::TMessageBus& messageBus
				);
				SearchWidgetController& GetSearchWidgetController() const;
				SearchProviders::MyTestSearchProvider& GetSearchProvider() const;
				ISearchResultsRepository& GetSuggestionsRepository() const;
				ISearchResultsRepository& GetSearchResultsRepository() const;
				~SearchWidgetViewModule();
			};
    	}
	}
}
