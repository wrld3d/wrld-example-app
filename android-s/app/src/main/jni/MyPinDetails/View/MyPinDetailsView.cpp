// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsView::MyPinDetailsView(AndroidNativeState& nativeState)
                :m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.mypindetails.MyPinDetailsView");
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_uiView = env->NewGlobalRef(instance);
            }

            MyPinDetailsView::~MyPinDetailsView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void MyPinDetailsView::OnDismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsView::OnRemove()
            {
                m_removePinCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsView::InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.AddCallback(callback);
            }

            void MyPinDetailsView::RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsView::OpenWithModel(
            		const std::string& title,
                    const std::string& description,
                    const std::string& imagePath)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring titleStr = env->NewStringUTF(title.c_str());
                jstring descriptionStr = env->NewStringUTF(description.c_str());
                jstring imageStr = env->NewStringUTF(imagePath.c_str());

                jmethodID showDetailsMethod = env->GetMethodID(m_uiViewClass, "display", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
                env->CallVoidMethod(m_uiView, showDetailsMethod, titleStr, descriptionStr, imageStr);

                env->DeleteLocalRef(titleStr);
                env->DeleteLocalRef(descriptionStr);
                env->DeleteLocalRef(imageStr);
            }

            void MyPinDetailsView::Close()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);
            }
        }
    }
}
