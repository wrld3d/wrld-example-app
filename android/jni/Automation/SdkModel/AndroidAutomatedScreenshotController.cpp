// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AndroidNativeState.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidAutomatedScreenshotController.h"
#include "AutomatedScreenshotController.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            AndroidAutomatedScreenshotController::AndroidAutomatedScreenshotController(AndroidNativeState& nativeState,
                                                                                       AutomatedScreenshotController& screenshotController)
                : m_nativeState(nativeState)
                , m_screenshotController(screenshotController)
                , m_screenshotsCompletedCallback(this, &AndroidAutomatedScreenshotController::OnScreenshotsCompleted)
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/automation/AutomatedScreenshotController");
                jclass klass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_class = static_cast<jclass>(env->NewGlobalRef(klass));
                jmethodID ctor = env->GetMethodID(m_class, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_class,
                                       ctor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_object = env->NewGlobalRef(instance);

                m_screenshotController.InsertCompletedScreenshotsCallback(m_screenshotsCompletedCallback);
            }

            AndroidAutomatedScreenshotController::~AndroidAutomatedScreenshotController()
            {
                m_screenshotController.RemoveCompletedScreenshotsCallback(m_screenshotsCompletedCallback);

                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                env->DeleteGlobalRef(m_object);
                env->DeleteGlobalRef(m_class);
            }

            void AndroidAutomatedScreenshotController::OnScreenshotsCompleted()
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID onScreenshotsCompleted = env->GetMethodID(m_class, "onScreenshotsCompleted", "()V");
                env->CallVoidMethod(m_object, onScreenshotsCompleted);
            }
        }
    }
}
