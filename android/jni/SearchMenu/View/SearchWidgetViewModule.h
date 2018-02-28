// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "ISearchWidgetView.h"
#include "MyTestSearchProvider.h"
#include "SearchServices.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchWidgetViewModule: private Eegeo::NonCopyable
			{
			private:
				SearchMenu::View::ISearchWidgetView* m_pSearchWidgetView;

				SearchProviders::MyTestSearchProvider* m_pMyTestSearchProvider;
				SearchMenu::View::SearchServices* m_pSearchServices;

			public:
				SearchWidgetViewModule(
					AndroidNativeState& nativeState,
					ExampleAppMessaging::TMessageBus& messageBus
				);

				~SearchWidgetViewModule();
			};
    	}
	}
}
