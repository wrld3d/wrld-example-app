// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidAppThreadAssertionMacros.h"
#include "SecondaryMenuView.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            void SecondaryMenuView::CallVoidVoidMethod(const char* func)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID jmethod = env->GetMethodID(m_uiViewClass, func, "()V");
                env->CallVoidMethod(m_uiView, jmethod);
            }

            SecondaryMenuView::SecondaryMenuView(AndroidNativeState& nativeState,
                                                 const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
            }

            void SecondaryMenuView::RemoveSeachKeyboard()
            {
                ASSERT_UI_THREAD
                CallVoidVoidMethod("removeSeachKeyboard");
            }

            void SecondaryMenuView::DisableEditText()
            {
                ASSERT_UI_THREAD
                CallVoidVoidMethod("disableEditText");
            }

            void SecondaryMenuView::EnableEditText()
            {
                ASSERT_UI_THREAD
                CallVoidVoidMethod("enableEditText");
            }

            void SecondaryMenuView::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.AddCallback(callback);
            }

            void SecondaryMenuView::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.RemoveCallback(callback);
            }

            void SecondaryMenuView::OnSearch(const std::string& searchTerm)
            {
                ASSERT_UI_THREAD
                m_callbacks.ExecuteCallbacks(searchTerm);
            }
        }
    }
}
