//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IndoorAtlasLocationManager.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "LatLongAltitude.h"
#include "IndoorLocationChangedMessage.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
		namespace View
		{
			IndoorAtlasLocationManager::IndoorAtlasLocationManager(ExampleApp::IndoorAtlas::IndoorAtlasLocationService* indoorAtlasLocationService
																   , AndroidNativeState& nativeState
																   , ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
			: m_pIndoorAtlasLocationService(indoorAtlasLocationService)
			, m_nativeState(nativeState)
			, m_messageBus(messageBus)
			, m_floorIndex(-1)
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("com/eegeo/indooratlas/IndoorAtlasManager");
				jclass uiClass = m_nativeState.LoadClass(env, strClassName);
				env->DeleteLocalRef(strClassName);

				m_jniApiClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
				jmethodID apiCtor = env->GetMethodID(m_jniApiClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

				jobject instance = env->NewObject(
						m_jniApiClass,
						apiCtor,
						m_nativeState.activity,
						(jlong)(this)
					);

				m_jniApiInstance = env->NewGlobalRef(instance);
			}

			IndoorAtlasLocationManager::~IndoorAtlasLocationManager()
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID jmethod = env->GetMethodID(m_jniApiClass, "destroy", "()V");
				env->CallVoidMethod(m_jniApiInstance, jmethod);

				env->DeleteGlobalRef(m_jniApiInstance);
				env->DeleteGlobalRef(m_jniApiClass);
			}

			void IndoorAtlasLocationManager::StartUpdatingLocation(std::string apiKey,
																   std::string apiSecret,
																   std::map<int, std::string> floorMap,
																   int floorIndex)
			{
				m_floorMap = floorMap;
				m_floorIndex = floorIndex;
				std::string floorPlanId = GetFloorPlanIdFromFloorIndex(floorIndex);

				if(floorPlanId!="")
				{
					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jstring apiKeyString = env->NewStringUTF(apiKey.c_str());
					jstring apiSecretString = env->NewStringUTF(apiSecret.c_str());

					jmethodID method = env->GetMethodID(m_jniApiClass, "StartUpdatingLocation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

					jstring floorPlanIdString = env->NewStringUTF(floorPlanId.c_str());
					env->CallVoidMethod(m_jniApiInstance, method, apiKeyString, apiSecretString, floorPlanIdString);
					env->DeleteLocalRef(floorPlanIdString);
					env->DeleteLocalRef(apiKeyString);
					env->DeleteLocalRef(apiSecretString);
				}
			}

			void IndoorAtlasLocationManager::StopUpdatingLocation()
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID jmethod = env->GetMethodID(m_jniApiClass, "StopUpdatingLocation", "()V");
				env->CallVoidMethod(m_jniApiInstance, jmethod);
			}

			void IndoorAtlasLocationManager::SetFloorIndex(int floorIndex)
			{
				m_floorIndex = floorIndex;
				std::string floorPlanId = GetFloorPlanIdFromFloorIndex(floorIndex);
				if(floorPlanId!=""){
					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID method = env->GetMethodID(m_jniApiClass, "SetFloorIndex", "(Ljava/lang/String;)V");

					jstring floorPlanIdString = env->NewStringUTF(floorPlanId.c_str());
					env->CallVoidMethod(m_jniApiInstance, method, floorPlanIdString);
					env->DeleteLocalRef(floorPlanIdString);
					m_pIndoorAtlasLocationService->SetFloorIndex(m_floorIndex);
				}
			}

			std::string IndoorAtlasLocationManager::GetFloorPlanIdFromFloorIndex(int floorIndex)
			{
				std::map<int, std::string>::iterator it = m_floorMap.find(floorIndex);

				if(it != m_floorMap.end())
				{
					return it->second;
				}

				return "";
			}

			void IndoorAtlasLocationManager::OnUpdateLocation(double latitude, double longitude)
			{
				ASSERT_UI_THREAD
				Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
				m_messageBus.Publish(ExampleApp::IndoorLocation::IndoorLocationChangedMessage(latLong));
				m_messageBus.FlushToNative();
			}
		}
    }
}

