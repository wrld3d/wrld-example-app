// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AndroidNativeState.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ScreengrabScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            ScreengrabScreenshotService::ScreengrabScreenshotService(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
                , m_class(NULL)
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("tools/fastlane/screengrab/Screengrab");
                jclass klass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_class = static_cast<jclass>(env->NewGlobalRef(klass));
            }

            ScreengrabScreenshotService::~ScreengrabScreenshotService()
            {
                if (m_class != NULL)
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv *env = attached.envForThread;

                    env->DeleteGlobalRef(m_class);
                }
            }

            void ScreengrabScreenshotService::screenshot(const std::string& filename)
            {
                if (m_class != NULL)
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv *env = attached.envForThread;

                    jmethodID screenshotMethod = env->GetStaticMethodID(m_class, "screenshot",
                                                                        "(Ljava/lang/String;)V");
                    env->CallStaticVoidMethod(m_class, screenshotMethod,
                                              env->NewStringUTF(filename.c_str()));
                }
            }
        }
    }
}
