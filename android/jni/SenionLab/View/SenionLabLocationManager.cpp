//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#include "SenionLabLocationManager.h"
#include "SenionLabLocationService.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "LatLongAltitude.h"
#include "SenionLabLocationChangedMessage.h"

namespace ExampleApp
{
    namespace SenionLab
    {
		namespace View
		{
			SenionLabLocationManager::SenionLabLocationManager(ExampleApp::SenionLab::SenionLabLocationService* pSenionLabLocationService,
															   ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
															   AndroidNativeState& nativeState )
			: m_pSenionLabLocationService(pSenionLabLocationService)
			, m_messageBus(messageBus)
			, m_nativeState(nativeState)
			, m_floorIndex(-1)
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("com/eegeo/senion/SenionLabLocationManager");
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

			SenionLabLocationManager::~SenionLabLocationManager()
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				env->DeleteGlobalRef(m_jniApiInstance);
				env->DeleteGlobalRef(m_jniApiClass);
			}

			void SenionLabLocationManager::StartUpdatingLocation(std::string apiKey,
															   	 std::string apiSecret,
															     std::map<int, std::string> floorMap)
			{
				Eegeo_TTY("senion StartUpdatingLocation");
				m_floorMap = floorMap;

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring mapKeyString = env->NewStringUTF(apiKey.c_str());
				jstring customerIdString = env->NewStringUTF(apiSecret.c_str());

				jmethodID jmethod = env->GetMethodID(m_jniApiClass, "StartUpdatingLocation", "(Ljava/lang/String;Ljava/lang/String;)V");
				env->CallVoidMethod(m_jniApiInstance,
									jmethod,
									mapKeyString,
									customerIdString);

				env->DeleteLocalRef(mapKeyString);
				env->DeleteLocalRef(customerIdString);
			}

			void SenionLabLocationManager::StopUpdatingLocation()
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID jmethod = env->GetMethodID(m_jniApiClass, "StopUpdatingLocation", "()V");
				env->CallVoidMethod(m_jniApiInstance, jmethod);
			}

			int SenionLabLocationManager::getFloorIndexFromSenionFloorIndex(std::string senionFloorIndex)
			{
				for(std::map<int, std::string>::iterator it = m_floorMap.begin(); it != m_floorMap.end(); ++it)
				{
					if(it->second == senionFloorIndex)
					{
						return it->first;
					}
				}
				return -1;
			}

			void SenionLabLocationManager::OnUpdateLocation(double latitude, double longitude, std::string senionFloorNo)
			{
				ASSERT_UI_THREAD;
				Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
				int floorNum = getFloorIndexFromSenionFloorIndex(senionFloorNo);
				m_messageBus.Publish(ExampleApp::SenionLab::SenionLabLocationChangedMessage(latLong, floorNum));
				m_messageBus.FlushToNative();
			}
		}
    }
}

