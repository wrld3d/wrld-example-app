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
                    jmethodID locationManagerInit = env->GetMethodID(m_locationManagerClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                    jobject instance = env->NewObject(m_locationManagerClass,
                                                      locationManagerInit,
                                                      m_nativeState.activity,
                                                      reinterpret_cast<jlong>(this));
                    m_locationManagerInstance = env->NewGlobalRef(instance);
                }

                IndoorAtlasLocationInterop::~IndoorAtlasLocationInterop()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    env->DeleteGlobalRef(m_locationManagerClass);
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

                    jstring apiKeyJString = env->NewStringUTF(apiKey.c_str());
                    jstring apiSecretJString = env->NewStringUTF(apiSecret.c_str());
                    env->CallVoidMethod(m_locationManagerInstance,
                                        startUpdatingLocation,
                                        apiKeyJString,
                                        apiSecretJString);
                    env->DeleteLocalRef(apiKeyJString);
                    env->DeleteLocalRef(apiSecretJString);
                }

                void IndoorAtlasLocationInterop::StopUpdating()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jmethodID stopUpdatingLocation = env->GetMethodID(m_locationManagerClass,
                                                                      "stopUpdatingLocation",
                                                                      "()V");

                    env->CallVoidMethod(m_locationManagerInstance, stopUpdatingLocation);
                }

                void IndoorAtlasLocationInterop::DidUpdateLocation(
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

                void IndoorAtlasLocationInterop::SetIsAuthorized(const bool isAuthorized)
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
