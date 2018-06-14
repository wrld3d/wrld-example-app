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
				SearchMenu::View::SearchWidgetView* m_pSearchWidgetView;
				SearchMenu::View::SearchWidgetController* m_pSearchWidgetController;

				SearchProviders::MyTestSearchProvider* m_pMyTestSearchProvider;
				SearchMenu::View::SearchServices* m_pSearchServices;

			public:
				SearchWidgetViewModule(
					AndroidNativeState& nativeState,
					Modality::View::IModalBackgroundView& modalBackgroundView,
					Menu::View::IMenuViewModel& viewModel,
					bool showNavigationButtons,
					ExampleAppMessaging::TMessageBus& messageBus
				);
				SearchWidgetController& GetSearchWidgetController() const;
				~SearchWidgetViewModule();
			};
    	}
	}
}
