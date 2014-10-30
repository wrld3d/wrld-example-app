// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidInitialExperiencePreLoadModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
    	namespace PreLoad
    	{
			AndroidInitialExperiencePreLoadModel::AndroidInitialExperiencePreLoadModel(
		    	AndroidNativeState& nativeState,
				WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel,
				PersistentSettings::IPersistentSettingsModel& persistentSettings
			)
			: InitialExperiencePreLoadModelBase(worldAreaLoaderModel, persistentSettings)
			, m_nativeState(nativeState)
			, m_jniApiClass(NULL)
			, m_jniApiInstance(NULL)
			{
			}

			AndroidInitialExperiencePreLoadModel::~AndroidInitialExperiencePreLoadModel()
			{
				DestroyOptions();
			}

			void AndroidInitialExperiencePreLoadModel::HandleDismiss(bool shouldPreload)
			{
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
	    		AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("com.eegeo.initialexperience.preload.PreLoadInitialExperience");
				jclass uiClass = m_nativeState.LoadClass(env, strClassName);
				env->DeleteLocalRef(strClassName);

				m_jniApiClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
				jmethodID ctor = env->GetMethodID(m_jniApiClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

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

JNIEXPORT void JNICALL Java_com_eegeo_initialexperience_preload_PreLoadInitialExperienceJniMethods_HandleSelection(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jboolean shouldPreload)
{
	ExampleApp::InitialExperience::PreLoad::AndroidInitialExperiencePreLoadModel* pApi = reinterpret_cast<ExampleApp::InitialExperience::PreLoad::AndroidInitialExperiencePreLoadModel*>(nativeObjectPtr);
	pApi->HandleDismiss(shouldPreload);
}

