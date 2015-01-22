// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>
#include "AndroidNativeState.h"
#include "Types.h"
#include "InitialExperiencePreLoadModelBase.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                class AndroidInitialExperiencePreLoadModel : public InitialExperiencePreLoadModelBase
                {
                    AndroidNativeState& m_nativeState;
                    jclass m_jniApiClass;
                    jobject m_jniApiInstance;

                    void DestroyOptions();

                public:
                    AndroidInitialExperiencePreLoadModel(
                        AndroidNativeState& nativeState,
                        WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                        PersistentSettings::IPersistentSettingsModel& persistentSettings
                    );

                    ~AndroidInitialExperiencePreLoadModel();

                    void HandleDismiss(bool shouldPreload);

                protected:

                    void ShowOptions();
                };
            }
        }
    }
}

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_initialexperience_preload_PreLoadInitialExperienceJniMethods_HandleSelection(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean shouldPreload);
}
