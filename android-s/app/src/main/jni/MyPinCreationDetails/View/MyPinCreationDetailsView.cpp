// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsView::MyPinCreationDetailsView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.mypincreationdetails.MyPinCreationDetailsView");
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

            MyPinCreationDetailsView::~MyPinCreationDetailsView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void MyPinCreationDetailsView::Open()
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID showDetailsMethod = env->GetMethodID(m_uiViewClass, "show", "()V");
                env->CallVoidMethod(m_uiView, showDetailsMethod);
            }

            void MyPinCreationDetailsView::Close()
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissDetailsMethod = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
                env->CallVoidMethod(m_uiView, dismissDetailsMethod);
            }

            void MyPinCreationDetailsView::OnConfirmed()
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsView::OnDismissed()
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationDetailsView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            std::string MyPinCreationDetailsView::GetTitle() const
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "getTitle", "()Ljava/lang/String;");
                jstring resultJString = static_cast<jstring>(env->CallObjectMethod(m_uiView, method));

                const char* titleChars = env->GetStringUTFChars(resultJString, 0);
                std::string titleString = titleChars;
                env->ReleaseStringUTFChars(resultJString, titleChars);

                return titleString;
            }

            std::string MyPinCreationDetailsView::GetDescription() const
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "getDescription", "()Ljava/lang/String;");
                jstring resultJString = static_cast<jstring>(env->CallObjectMethod(m_uiView, method));

                const char* descChars = env->GetStringUTFChars(resultJString, 0);
                std::string descString = descChars;
                env->ReleaseStringUTFChars(resultJString, descChars);

                return descString;
            }

            bool MyPinCreationDetailsView::ShareSelected() const
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "getShouldShare", "()Z");
                jboolean result = env->CallBooleanMethod(m_uiView, method);

                return result;
            }

            Byte* MyPinCreationDetailsView::GetImageBuffer() const
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "getImageBuffer", "()[B");
                jbyteArray array = static_cast<jbyteArray>(env->CallObjectMethod(m_uiView, method));

                Byte* imageDataBytes = NULL;
                jbyte* pBuffer = NULL;

                if(array != NULL)
                {
                    pBuffer = env->GetByteArrayElements(array, NULL);
                    imageDataBytes = reinterpret_cast<Byte *>(pBuffer);
                    env->ReleaseByteArrayElements(array, pBuffer, 0);
                }

                return imageDataBytes;
            }

            size_t MyPinCreationDetailsView::GetImageSize() const
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "getImageBufferSize", "()I");
                jint result = env->CallIntMethod(m_uiView, method);

                return result;
            }

            void MyPinCreationDetailsView::ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setConnectivityMethod = env->GetMethodID(m_uiViewClass, "setHasNetworkConnectivity", "(ZZ)V");
                env->CallVoidMethod(m_uiView, setConnectivityMethod, hasConnectivity, shouldVerifyShareSettings);
            }
        }
    }
}

