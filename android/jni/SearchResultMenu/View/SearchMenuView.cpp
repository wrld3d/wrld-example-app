// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchMenuView::SearchMenuView(AndroidNativeState& nativeState,
                                           const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
            }

            void SearchMenuView::SetHeader(const std::string& header, bool queryPending, size_t numResult)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateHeaderMethod = env->GetMethodID(m_uiViewClass, "updateHeader", "(Ljava/lang/String;ZI)V");
                jstring queryString = env->NewStringUTF(header.c_str());

                env->CallVoidMethod(m_uiView, updateHeaderMethod, queryString, queryPending, numResult);
                env->DeleteLocalRef(queryString);
            }

            void SearchMenuView::HandleSearchClosed()
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.ExecuteCallbacks();
            }

            void SearchMenuView::SetAttractMode(bool attractModeEnabled)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setAttractModeMethod = env->GetMethodID(m_uiViewClass, "setAttractMode", "(Z)V");
                env->CallVoidMethod(m_uiView, setAttractModeMethod, attractModeEnabled);
            }

            void SearchMenuView::InsertSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
