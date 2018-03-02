// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "JniHelper.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
			SearchWidgetView::SearchWidgetView(AndroidNativeState& nativeState,
											   SearchProviders::MyTestSearchProvider& searchProvider)
			: m_nativeState(nativeState) {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv *env = attached.envForThread;

                m_uiViewClass = Helpers::JniHelper::LoadClassGlobalRef(
                        m_nativeState, env,
                        "com/eegeo/searchmenu/SearchWidgetView");
                m_uiView = Helpers::JniHelper::LoadInstanceGlobalRef(
                        env,
                        "(Lcom/eegeo/entrypointinfrastructure/MainActivity;"
                                "J"
                                "Lcom/wrld/widgets/searchbox/model/SearchProvider;)V",
                        m_uiViewClass,
                        m_nativeState.activity,
                        (jlong) this,
                        searchProvider.GetJavaInstance());
            }

            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {

            }

            void SearchWidgetView::OnSearchResultsCleared()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
