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
                SearchWidgetView* m_pSearchWidgetView;
                
                SearchMenu::View::SearchServices* m_pSearchServices;
                SearchProviders::SearchProvider* m_pSearchProvider;
            public:
                SearchWidgetViewModule(
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       Menu::View::IMenuViewModel& viewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus
                                       );
                
                ~SearchWidgetViewModule();
                
                SearchWidgetView& GetSearchWidgetView() const;
                SearchWidgetController& GetSearchWidgetController() const;
            };
        }
    }
}
