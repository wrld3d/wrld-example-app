//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#include "SenionLabLocationManager.h"
#include "SenionLabLocationService.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "LatLongAltitude.h"
#include "InteriorsPositionLocationChangedMessage.h"

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
			, m_startUpdatingLocationCallback(this, &SenionLabLocationManager::OnStartUpdatingLocation)
            , m_stopUpdatingLocationCallback(this, &SenionLabLocationManager::OnStopUpdatingLocation)
			{
			    ASSERT_UI_THREAD
                m_messageBus.SubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.SubscribeUi(m_stopUpdatingLocationCallback);

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
			    m_messageBus.UnsubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.UnsubscribeUi(m_stopUpdatingLocationCallback);

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				env->DeleteGlobalRef(m_jniApiInstance);
				env->DeleteGlobalRef(m_jniApiClass);
			}

			void SenionLabLocationManager::StartUpdatingLocation(std::string apiKey,
															   	 std::string apiSecret,
															     std::map<int, std::string> floorMap)
			{
			    ASSERT_UI_THREAD
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
			    ASSERT_UI_THREAD
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
				m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionLocationChangedMessage(latLong, floorNum));
			}

			void SenionLabLocationManager::OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage)
			{
			    ASSERT_UI_THREAD
                StartUpdatingLocation(startUpdatingLocationMessage.GetApiKey(),
                                      startUpdatingLocationMessage.GetApiSecret(),
                                      startUpdatingLocationMessage.GetFloorMap());

			}

			void SenionLabLocationManager::OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage)
			{
			    ASSERT_UI_THREAD
                StopUpdatingLocation();
			}
		}
    }
}

