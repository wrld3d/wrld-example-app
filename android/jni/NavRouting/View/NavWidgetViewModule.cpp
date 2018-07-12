// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModule.h"
#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "MyTestSearchProvider.h"
#include "ISearchResultsRepository.h"
#include "SearchServicesResult.h"
#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetViewModule::NavWidgetViewModule(
                AndroidNativeState& nativeState,
                INavWidgetViewModel& navWidgetViewModel,
                SearchProviders::MyTestSearchProvider& navSearchProvider,
                SearchMenu::View::ISearchResultsRepository& searchResultsRepository,
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewTopHeightChangedCallbacks,
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewBottomHeightChangedCallbacks,
                ExampleAppMessaging::TMessageBus& messageBus)
            {
                ASSERT_UI_THREAD

                m_pMyTestSearchProvider = Eegeo_NEW(SearchProviders::MyTestSearchProvider)(
                        nativeState,
                        false
                );

                m_pView = Eegeo_NEW(NavWidgetView)(nativeState,
                                                   navSearchProvider,
                                                   navWidgetViewTopHeightChangedCallbacks,
                                                   navWidgetViewBottomHeightChangedCallbacks);

                m_pController = Eegeo_NEW(NavWidgetController)(*m_pView,
                                                               navWidgetViewModel,
                                                               searchResultsRepository,
                                                               messageBus);
            }

            NavWidgetViewModule::~NavWidgetViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
                Eegeo_DELETE m_pMyTestSearchProvider;
            }

            INavWidgetView& NavWidgetViewModule::GetView() const
            {
                return *m_pView;
            }

            NavWidgetController& NavWidgetViewModule::GetController() const
            {
                return *m_pController;
            }
        }
    }
}
