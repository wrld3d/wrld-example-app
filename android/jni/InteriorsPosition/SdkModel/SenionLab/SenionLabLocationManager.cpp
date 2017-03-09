// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>
#include <sstream>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "SenionLabLocationService.h"
#include "SenionLabLocationManager.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationManager::SenionLabLocationManager(SenionLabLocationService& senionLabLocationService,
                                                                   ExampleAppMessaging::TMessageBus &messageBus,
                                                                   AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
                , m_senionLabLocationService(senionLabLocationService)
                , m_messageBus(messageBus)
                , m_onDidUpdateLocationCallback(this, &SenionLabLocationManager::OnDidUpdateLocation)
                , m_onSetIsAuthorized(this, &SenionLabLocationManager::OnSetIsAuthorized)
                , m_apiKey("")
                , m_apiSecret("")
                , m_isActive(false)
                {
                    ASSERT_NATIVE_THREAD

                    m_messageBus.SubscribeNative(m_onDidUpdateLocationCallback);
                    m_messageBus.SubscribeNative(m_onSetIsAuthorized);

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jstring locationManagerClassName = env->NewStringUTF("com/eegeo/interiorsposition/senionlab/SenionLabLocationManager");
                    jclass locationManagerClass = m_nativeState.LoadClass(env, locationManagerClassName);
                    env->DeleteLocalRef(locationManagerClassName);

                    m_locationManagerClass = static_cast<jclass>(env->NewGlobalRef(locationManagerClass));
                    jmethodID locationManagerInit = env->GetMethodID(m_locationManagerClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                    jobject instance = env->NewObject(m_locationManagerClass,
                                                      locationManagerInit,
                                                      m_nativeState.activity,
                                                      reinterpret_cast<jlong>(this));
                    m_locationManagerInstance = env->NewGlobalRef(instance);
                }

                SenionLabLocationManager::~SenionLabLocationManager()
                {
                    ASSERT_NATIVE_THREAD

                    m_messageBus.UnsubscribeNative(m_onSetIsAuthorized);
                    m_messageBus.UnsubscribeNative(m_onDidUpdateLocationCallback);

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    env->DeleteGlobalRef(m_locationManagerClass);
                }

                void SenionLabLocationManager::StartUpdatingLocation(const std::string& apiKey,
                                                                     const std::string& apiSecret,
                                                                     const std::map<int, std::string>& floorMap)
                {
                    m_floorMap = floorMap;
                    m_apiKey = apiKey;
                    m_apiSecret = apiSecret;
                    m_isActive = true;

                    AskUserToEnableBluetoothIfDisabled();
                    StartLocationUpdates();
                }

                void SenionLabLocationManager::StopUpdatingLocation()
                {
                    StopLocationUpdates();
                }

                jobject SenionLabLocationManager::ManagedInstance() const
                {
                    return m_locationManagerInstance;
                }

                void SenionLabLocationManager::OnDidUpdateLocation(const InteriorsLocationChangedMessage& message)
                {
                    Eegeo::Space::LatLong location(Eegeo::Space::LatLong::FromDegrees(message.Latitude(), message.Longitude()));
                    m_senionLabLocationService.SetLocation(location);
                    m_senionLabLocationService.SetFloorIndex(FloorNumberToFloorIndex(message.FloorNumber()));
                }

                void SenionLabLocationManager::OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message)
                {
                    m_senionLabLocationService.SetIsAuthorized(message.IsAuthorized());
                }

                int SenionLabLocationManager::FloorNumberToFloorIndex(const int floorIndex)
                {
                    std::stringstream floorNameStream;
                    floorNameStream << floorIndex;
                    std::string floorName(floorNameStream.str());

                    for (auto &kv : m_floorMap)
                    {
                        if (kv.second == floorName)
                        {
                            return kv.first;
                        }
                    }

                    return floorIndex;
                }

                void SenionLabLocationManager::OnResume()
                {
                	if(m_isActive)
                	{
                		StartLocationUpdates();
                	}
                }

                void SenionLabLocationManager::OnPause()
                {
                	if(m_isActive)
                	{
                		StopLocationUpdates();
                	}
                }

                void SenionLabLocationManager::AskUserToEnableBluetoothIfDisabled()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jmethodID askUserToEnableBluetoothIfDisabled = env->GetMethodID(m_locationManagerClass,
                                                                                    "askUserToEnableBluetoothIfDisabled",
                                                                                    "()V");

                    env->CallVoidMethod(m_locationManagerInstance, askUserToEnableBluetoothIfDisabled);
                }

                void SenionLabLocationManager::StartLocationUpdates()
                {
                	ASSERT_NATIVE_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID startUpdatingLocation = env->GetMethodID(m_locationManagerClass,
																	   "startUpdatingLocation",
																	   "(Ljava/lang/String;Ljava/lang/String;)V");

					jstring apiKeyJString = env->NewStringUTF(m_apiKey.c_str());
					jstring apiSecretJString = env->NewStringUTF(m_apiSecret.c_str());
					env->CallVoidMethod(m_locationManagerInstance,
										startUpdatingLocation,
										apiKeyJString,
										apiSecretJString);
					env->DeleteLocalRef(apiKeyJString);
					env->DeleteLocalRef(apiSecretJString);
                }

                void SenionLabLocationManager::StopLocationUpdates()
                {
                	ASSERT_NATIVE_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID stopUpdatingLocation = env->GetMethodID(m_locationManagerClass,
																	  "stopUpdatingLocation",
																	  "()V");

					env->CallVoidMethod(m_locationManagerInstance, stopUpdatingLocation);
                }
            }
        }
    }
}
