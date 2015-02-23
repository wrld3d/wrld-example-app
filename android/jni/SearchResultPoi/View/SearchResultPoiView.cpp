// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiView::SearchResultPoiView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/searchresultpoiview/SearchResultPoiView");
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_uiView = env->NewGlobalRef(instance);
            }

            SearchResultPoiView::~SearchResultPoiView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel model, bool isPinned)
            {
                ASSERT_UI_THREAD

                m_model = model;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
                jstring addressStr = env->NewStringUTF(model.GetAddress().c_str());
                jstring phoneStr = env->NewStringUTF(model.GetPhone().c_str());
                jstring urlStr = env->NewStringUTF(model.GetWebUrl().c_str());
                jstring categoryStr = env->NewStringUTF(model.GetCategory().c_str());

                jmethodID displayPoiInfo = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
                env->CallVoidMethod(m_uiView, displayPoiInfo, titleStr, addressStr, phoneStr, urlStr, categoryStr, isPinned);

                env->DeleteLocalRef(urlStr);
                env->DeleteLocalRef(phoneStr);
                env->DeleteLocalRef(addressStr);
                env->DeleteLocalRef(titleStr);
                env->DeleteLocalRef(categoryStr);
            }

            void SearchResultPoiView::Hide()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissPoiInfo", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);
            }

            void SearchResultPoiView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiView::HandleCloseClicked()
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.ExecuteCallbacks();
            }

            void SearchResultPoiView::InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiView::RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiView::HandlePinToggleClicked()
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.ExecuteCallbacks(m_model);
            }
        }
    }
}
