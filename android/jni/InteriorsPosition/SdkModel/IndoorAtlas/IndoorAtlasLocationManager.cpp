// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>
#include <sstream>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "IndoorAtlasLocationService.h"
#include "IndoorAtlasLocationManager.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationManager::IndoorAtlasLocationManager(IndoorAtlasLocationService& indoorAtlasLocationService,
                                                                       ExampleAppMessaging::TMessageBus &messageBus,
                                                                       AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
                , m_indoorAtlasLocationService(indoorAtlasLocationService)
                , m_onDidUpdateLocationCallback(this, &IndoorAtlasLocationManager::OnDidUpdateLocation)
                , m_onSetIsAuthorized(this, &IndoorAtlasLocationManager::OnSetIsAuthorized)
                {
                    ASSERT_NATIVE_THREAD

                    m_messageBus.SubscribeNative(m_onDidUpdateLocationCallback);
                    m_messageBus.SubscribeNative(m_onSetIsAuthorized);

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jstring locationManagerClassName = env->NewStringUTF("com/eegeo/interiorsposition/indooratlas/IndoorAtlasLocationManager");
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

                IndoorAtlasLocationManager::~IndoorAtlasLocationManager()
                {
                    ASSERT_NATIVE_THREAD

                    m_messageBus.UnsubscribeNative(m_onSetIsAuthorized);
                    m_messageBus.UnsubscribeNative(m_onDidUpdateLocationCallback);

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    env->DeleteGlobalRef(m_locationManagerClass);
                }

                void IndoorAtlasLocationManager::StartUpdatingLocation(const std::string& apiKey,
                                                                       const std::string& apiSecret,
                                                                       const std::map<int, std::string>& floorMap)
                {
                    ASSERT_NATIVE_THREAD

                    m_floorMap = floorMap;

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jmethodID startUpdatingLocation = env->GetMethodID(m_locationManagerClass,
                                                                       "startUpdatingLocation",
                                                                       "(Ljava/lang/String;Ljava/lang/String;)V");

                    jstring apiKeyJString = env->NewStringUTF(apiKey.c_str());
                    jstring apiSecretJString = env->NewStringUTF(apiSecret.c_str());
                    env->CallVoidMethod(m_locationManagerInstance,
                                        startUpdatingLocation,
                                        apiKeyJString,
                                        apiSecretJString);
                    env->DeleteLocalRef(apiKeyJString);
                    env->DeleteLocalRef(apiSecretJString);
                }

                void IndoorAtlasLocationManager::StopUpdatingLocation()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jmethodID stopUpdatingLocation = env->GetMethodID(m_locationManagerClass,
                                                                      "stopUpdatingLocation",
                                                                      "()V");

                    env->CallVoidMethod(m_locationManagerInstance, stopUpdatingLocation);
                }

                void IndoorAtlasLocationManager::DidUpdateLocation(const double latitude, const double longitude, const std::string& floorId)
                {
                    ASSERT_UI_THREAD
                    int wrldFloorId;
                    if(!TryMapFloorIdToFloorIndex(floorId, wrldFloorId))
                    {
                        wrldFloorId = -1;
                    }

                    m_messageBus.Publish(InteriorsLocationChangedMessage(latitude, longitude, wrldFloorId));
                    m_messageBus.Publish(AboutPage::AboutPageIndoorAtlasDataMessage(wrldFloorId, floorId, latitude, longitude));
                }

                void IndoorAtlasLocationManager::SetIsAuthorized(const bool isAuthorized)
                {
                    ASSERT_UI_THREAD
                    m_messageBus.Publish(InteriorsLocationAuthorizationChangedMessage(isAuthorized));
                }

                void IndoorAtlasLocationManager::OnDidUpdateLocation(const InteriorsLocationChangedMessage& message)
                {
                    ASSERT_NATIVE_THREAD
                    Eegeo::Space::LatLong location(Eegeo::Space::LatLong::FromDegrees(message.Latitude(), message.Longitude()));
                    m_indoorAtlasLocationService.SetLocation(location);
                    m_indoorAtlasLocationService.SetFloorIndex(message.FloorNumber());
                }

                void IndoorAtlasLocationManager::OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message)
                {
                	ASSERT_NATIVE_THREAD
                	m_indoorAtlasLocationService.SetIsAuthorized(message.IsAuthorized());
                }

                bool IndoorAtlasLocationManager::TryMapFloorIdToFloorIndex(const std::string floorId, int& wrldFloorId)
                {
                    for (auto &kv : m_floorMap)
                    {
                        if (kv.second == floorId)
                        {
                            wrldFloorId =  kv.first;
                            return true;
                        }
                    }

                    wrldFloorId = -1;
                    return false;
                }
            }
        }
    }
}
