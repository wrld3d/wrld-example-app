// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <vector>
#include <jni.h>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "AlbumScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            AlbumScreenshotService::AlbumScreenshotService(AndroidNativeState& nativeState, SurfaceScreenshotService& surfaceScreenshotService)
                : m_nativeState(nativeState)
                , m_surfaceScreenshotService(surfaceScreenshotService)
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/automation/AsyncSurfaceScreenshotCompositor");
                jclass klass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);
                m_screenshotCompositorClass = static_cast<jclass>(env->NewGlobalRef(klass));

                strClassName = env->NewStringUTF("com/eegeo/automation/AlbumScreenshotService");
                klass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);
                m_class = static_cast<jclass>(env->NewGlobalRef(klass));

                jmethodID ctor = env->GetMethodID(m_class, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_class,
                                       ctor,
                                       m_nativeState.activity,
                                       (jlong) this
                                   );

                m_object = env->NewGlobalRef(instance);
            }

            AlbumScreenshotService::~AlbumScreenshotService()
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                env->DeleteGlobalRef(m_object);
                env->DeleteGlobalRef(m_class);
                env->DeleteGlobalRef(m_screenshotCompositorClass);
            }

            void AlbumScreenshotService::screenshot(const std::string& screenshotName)
            {
                ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID screenshot = env->GetMethodID(m_class, "screenshot", "(Ljava/lang/String;)V");
                env->CallVoidMethod(m_object, screenshot, env->NewStringUTF(screenshotName.c_str()));
            }

            void AlbumScreenshotService::AsyncSurfaceScreenshot(jobject compositor)
            {
                ASSERT_NATIVE_THREAD
                
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                const jobject compositorObject = env->NewGlobalRef(compositor);
                m_surfaceScreenshotService.Screenshot([this, compositorObject](long width, long height, const std::vector<GLubyte>& surfaceBytes) {
                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;
                    jmethodID run = env->GetMethodID(m_screenshotCompositorClass, "run", "(JJ[B)V");
                    jbyteArray javaSurfaceBytes = env->NewByteArray(surfaceBytes.size());
                    env->SetByteArrayRegion(javaSurfaceBytes, 0, surfaceBytes.size(), (jbyte*) &surfaceBytes[0]);
                    env->CallVoidMethod(compositorObject, run, static_cast<jlong>(width), static_cast<jlong>(height), javaSurfaceBytes);
                    env->DeleteLocalRef(javaSurfaceBytes);
                    env->DeleteGlobalRef(compositorObject);
                });
            }
        }
    }
}
