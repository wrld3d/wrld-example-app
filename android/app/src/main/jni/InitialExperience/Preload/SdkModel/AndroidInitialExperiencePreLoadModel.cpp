// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidInitialExperiencePreLoadModel.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                AndroidInitialExperiencePreLoadModel::AndroidInitialExperiencePreLoadModel(
                    AndroidNativeState& nativeState,
                    WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings
                )
                    : InitialExperiencePreLoadModelBase(worldAreaLoaderModel, persistentSettings)
                    , m_nativeState(nativeState)
                    , m_jniApiClass(NULL)
                    , m_jniApiInstance(NULL)
                {
                    ASSERT_NATIVE_THREAD
                }

                AndroidInitialExperiencePreLoadModel::~AndroidInitialExperiencePreLoadModel()
                {
                    ASSERT_NATIVE_THREAD

                    DestroyOptions();
                }

                void AndroidInitialExperiencePreLoadModel::HandleDismiss(bool shouldPreload)
                {
                    ASSERT_NATIVE_THREAD

                    DestroyOptions();

                    if(shouldPreload)
                    {
                        PrecacheRegion();
                    }
                    else
                    {
                        Complete();
                    }
                }

                void AndroidInitialExperiencePreLoadModel::DestroyOptions()
                {
                    ASSERT_NATIVE_THREAD

                    if(m_jniApiInstance != NULL)
                    {
                        AndroidSafeNativeThreadAttachment attached(m_nativeState);
                        JNIEnv* env = attached.envForThread;
                        jmethodID removeHudMethod = env->GetMethodID(m_jniApiClass, "destroy", "()V");
                        env->CallVoidMethod(m_jniApiInstance, removeHudMethod);
                        env->DeleteGlobalRef(m_jniApiInstance);
                        env->DeleteGlobalRef(m_jniApiClass);
                        m_jniApiInstance = NULL;
                        m_jniApiClass = NULL;
                    }
                }

                void AndroidInitialExperiencePreLoadModel::ShowOptions()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jstring strClassName = env->NewStringUTF("com.eegeo.initialexperience.preload.PreLoadInitialExperience");
                    jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                    env->DeleteLocalRef(strClassName);

                    m_jniApiClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                    jmethodID ctor = env->GetMethodID(m_jniApiClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                    jobject instance = env->NewObject(
                                           m_jniApiClass,
                                           ctor,
                                           m_nativeState.activity,
                                           (jlong)(this)
                                       );

                    m_jniApiInstance = env->NewGlobalRef(instance);
                }
            }
        }
    }
}

JNIEXPORT void JNICALL Java_com_eegeo_initialexperience_preload_PreLoadInitialExperienceJniMethods_HandleSelection(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jboolean shouldPreload)
{
    ASSERT_NATIVE_THREAD

    ExampleApp::InitialExperience::PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel* pApi = reinterpret_cast<ExampleApp::InitialExperience::PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel*>(nativeObjectPtr);
    pApi->HandleDismiss(shouldPreload);
}

