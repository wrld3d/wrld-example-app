// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationInterop.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "IndoorAtlasLocationService.h"

#include <jni.h>
#include <sstream>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationInterop::IndoorAtlasLocationInterop(AndroidNativeState& nativeState)
                : m_pIndoorAtlasLocationService(nullptr)
                , m_nativeState(nativeState)
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jclass locationManagerClass = m_nativeState.LoadClass(env, "com/eegeo/interiorsposition/indooratlas/IndoorAtlasLocationInterop");
                    m_locationManagerClass = static_cast<jclass>(env->NewGlobalRef(locationManagerClass));
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(m_locationManagerClass != nullptr);

                    jmethodID locationManagerInit = env->GetMethodID(m_locationManagerClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(locationManagerInit != nullptr);

                    jobject instance = env->NewObject(m_locationManagerClass,
                                                      locationManagerInit,
                                                      m_nativeState.activity,
                                                      reinterpret_cast<jlong>(this));
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(instance != nullptr);

                    m_locationManagerInstance = env->NewGlobalRef(instance);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(m_locationManagerInstance != nullptr);
                }

                IndoorAtlasLocationInterop::~IndoorAtlasLocationInterop()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    env->DeleteGlobalRef(m_locationManagerClass);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                }

                void IndoorAtlasLocationInterop::SetLocationService(IndoorAtlasLocationService* pLocationService)
                {
                    Eegeo_ASSERT(pLocationService != nullptr);
                    m_pIndoorAtlasLocationService = pLocationService;
                }

                void IndoorAtlasLocationInterop::StartUpdating(const std::string& apiKey,
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
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(startUpdatingLocation != nullptr);

                    jstring apiKeyJString = env->NewStringUTF(apiKey.c_str());
                    jstring apiSecretJString = env->NewStringUTF(apiSecret.c_str());
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    env->CallVoidMethod(m_locationManagerInstance,
                                        startUpdatingLocation,
                                        apiKeyJString,
                                        apiSecretJString);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    env->DeleteLocalRef(apiKeyJString);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    env->DeleteLocalRef(apiSecretJString);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                }

                void IndoorAtlasLocationInterop::StopUpdating()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jmethodID stopUpdatingLocation = env->GetMethodID(m_locationManagerClass,
                                                                      "stopUpdatingLocation",
                                                                      "()V");
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(stopUpdatingLocation != nullptr)

                    env->CallVoidMethod(m_locationManagerInstance, stopUpdatingLocation);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                }

                void IndoorAtlasLocationInterop::UpdateLocation(
                        const double latitudeDegrees,
                        const double longitudeDegrees,
                        const double horizontalAccuracyInMeters,
                        const std::string& floorId)
                {
                    ASSERT_NATIVE_THREAD

                    int wrldFloorIndex;
                    if(!TryMapFloorIdToFloorIndex(floorId, wrldFloorIndex))
                    {
                        wrldFloorIndex = -1;
                    }

                    m_pIndoorAtlasLocationService->SetLocation(Eegeo::Space::LatLong::FromDegrees(latitudeDegrees, longitudeDegrees));
                    m_pIndoorAtlasLocationService->SetHorizontalAccuracy(horizontalAccuracyInMeters);
                    m_pIndoorAtlasLocationService->SetFloor(floorId, wrldFloorIndex);
                }

                void IndoorAtlasLocationInterop::UpdateIsAuthorized(const bool isAuthorized)
                {
                    ASSERT_NATIVE_THREAD
                    m_pIndoorAtlasLocationService->SetIsAuthorized(isAuthorized);
                }

                bool IndoorAtlasLocationInterop::TryMapFloorIdToFloorIndex(const std::string floorId, int& wrldFloorId)
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
