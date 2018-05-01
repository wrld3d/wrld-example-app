// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchVendorNames.h"
#include "YelpSearchResultModel.h"
#include "YelpParsingHelpers.h"
#include "EegeoJsonParser.h"
#include "EegeoSearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetView::NavWidgetView(AndroidNativeState& nativeState)
                    : m_nativeState(nativeState)
                    , m_uiViewClass(NULL)
                    , m_uiView(NULL)
            {
                ASSERT_UI_THREAD
            }

            NavWidgetView::~NavWidgetView()
            {
                ASSERT_UI_THREAD
            }

            void NavWidgetView::Show()
            {
                ASSERT_UI_THREAD
                const std::string viewClass = "com/eegeo/navwidget/NavWidgetView";
                m_uiViewClass = CreateJavaClass(viewClass);
                Eegeo_ASSERT(m_uiViewClass != NULL, "failed to create viewClass NavWidgetView");
                m_uiView = CreateJavaObject(m_uiViewClass);
                Eegeo_ASSERT(m_uiView != NULL, "failed to create view NavWidgetView");
            }

            void NavWidgetView::Hide()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissNavWidgetView", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);

                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);

                m_uiViewClass = NULL;
                m_uiView = NULL;
            }

            void NavWidgetView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleCloseClicked()
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.ExecuteCallbacks();
            }

            jclass NavWidgetView::CreateJavaClass(const std::string& viewClass)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF(viewClass.c_str());
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                return static_cast<jclass>(env->NewGlobalRef(uiClass));
            }

            jobject NavWidgetView::CreateJavaObject(jclass uiViewClass)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID uiViewCtor = env->GetMethodID(uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                        uiViewClass,
                        uiViewCtor,
                        m_nativeState.activity,
                        (jlong)(this)
                );

                return env->NewGlobalRef(instance);
            }

            jobjectArray NavWidgetView::CreateJavaArray(const std::vector<std::string>& stringVector)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jobjectArray jniStringArray = env->NewObjectArray(
                        stringVector.size(),
                        env->FindClass("java/lang/String"),
                        0
                );

                for(size_t i = 0; i < stringVector.size(); ++ i)
                {
                    jstring jniString = env->NewStringUTF(stringVector[i].c_str());
                    env->SetObjectArrayElement(jniStringArray, i, jniString);
                    env->DeleteLocalRef(jniString);
                }

                return jniStringArray;
            }
        }
    }
}
