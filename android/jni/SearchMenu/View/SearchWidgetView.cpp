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
			: m_nativeState(nativeState)
            {
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

                m_onSearchRefreshed = env->GetMethodID(m_uiViewClass,
                                                       "onSearchRefreshed",
                                                       "(Ljava/lang/String;ZZDDDF)V");
            }

            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {

            }

            void SearchWidgetView::RefreshSearch(const std::string& query, const QueryContext& context)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring text = env->NewStringUTF(query.c_str());

                env->CallVoidMethod(m_uiView,
                                    m_onSearchRefreshed,
                                    text,
                                    (jboolean)context.GetIsTag(),
                                    (jboolean)context.GetShouldTryInterior(),
                                    (jdouble)context.GetLocation().GetLongitude(),
                                    (jdouble)context.GetLocation().GetLatitude(),
                                    (jdouble)context.GetLocation().GetAltitude(),
                                    (jfloat)context.GetRadius());

                env->DeleteLocalRef(text);
            }

            void SearchWidgetView::OnSearchResultsCleared()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::OnSearchResultSelected(int index)
            {
                m_resultSelectedCallbacks.ExecuteCallbacks(index);
            }

            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
