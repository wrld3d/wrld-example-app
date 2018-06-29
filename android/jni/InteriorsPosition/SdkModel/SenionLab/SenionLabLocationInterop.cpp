// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationInterop.h"

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "SenionLabLocationService.h"

#include <jni.h>
#include <sstream>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationInterop::SenionLabLocationInterop(ExampleAppMessaging::TMessageBus &messageBus,
                                                                   AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
                , m_pSenionLabLocationService(nullptr)
                , m_messageBus(messageBus)
                , m_apiKey("")
                , m_apiSecret("")
                , m_isActive(false)
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jclass locationManagerClass = m_nativeState.LoadClass(env, "com/eegeo/interiorsposition/senionlab/SenionLabLocationInterop");

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

                SenionLabLocationInterop::~SenionLabLocationInterop()
                {
                    ASSERT_NATIVE_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    env->DeleteGlobalRef(m_locationManagerClass);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                }

                void SenionLabLocationInterop::SetLocationService(SenionLabLocationService *pLocationService)
                {
                    ASSERT_NATIVE_THREAD

                    Eegeo_ASSERT(pLocationService != nullptr);
                    m_pSenionLabLocationService = pLocationService;
                }


                void SenionLabLocationInterop::UpdateLocation(double latitudeDegrees,
                                                              double longtitudeDegrees,
                                                              double horizontalAccuracyInMeters,
                                                              int senionFloorNumber)
                {
                    ASSERT_NATIVE_THREAD

                    m_pSenionLabLocationService->SetLocationFromSenionData(
                            Eegeo::Space::LatLong::FromDegrees(latitudeDegrees, longtitudeDegrees),
                            senionFloorNumber,
                            FloorNumberToFloorIndex(senionFloorNumber),
                            horizontalAccuracyInMeters);
                }

                void SenionLabLocationInterop::UpdateHeading(double headingInDegrees)
                {
                    ASSERT_NATIVE_THREAD

                    m_pSenionLabLocationService->SetHeadingFromSenionData(headingInDegrees, true);
                }

                void SenionLabLocationInterop::UpdateIsAuthorized(bool isAuthorized)
                {
                    ASSERT_NATIVE_THREAD

                    m_pSenionLabLocationService->SetIsAuthorized(isAuthorized);
                }

                void SenionLabLocationInterop::StartUpdatingLocation(const std::string& apiKey,
                                                                     const std::string& apiSecret,
                                                                     const std::map<int, std::string>& floorMap)
                {
                    m_floorMap = floorMap;
                    m_apiKey = apiKey;
                    m_apiSecret = apiSecret;
                    m_isActive = true;

                    StartLocationUpdates();
                }

                void SenionLabLocationInterop::StopUpdatingLocation()
                {
                    StopLocationUpdates();
                }

                int SenionLabLocationInterop::FloorNumberToFloorIndex(const int senionFloorNumber)
                {
                    std::stringstream floorNameStream;
                    floorNameStream << senionFloorNumber;
                    std::string floorName(floorNameStream.str());

                    for (auto &kv : m_floorMap)
                    {
                        if (kv.second == floorName)
                        {
                            return kv.first;
                        }
                    }

                    return senionFloorNumber;
                }

                void SenionLabLocationInterop::OnResume()
                {
                	if(m_isActive)
                	{
                		StartLocationUpdates();
                	}
                }

                void SenionLabLocationInterop::OnPause()
                {
                	if(m_isActive)
                	{
                		StopLocationUpdates();
                	}
                }

                void SenionLabLocationInterop::StartLocationUpdates()
                {
                	ASSERT_NATIVE_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID startUpdatingLocation = env->GetMethodID(m_locationManagerClass,
																	   "startUpdatingLocation",
																	   "(Ljava/lang/String;Ljava/lang/String;)V");
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(startUpdatingLocation != nullptr);

					jstring apiKeyJString = env->NewStringUTF(m_apiKey.c_str());
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);

                    jstring apiSecretJString = env->NewStringUTF(m_apiSecret.c_str());
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

                void SenionLabLocationInterop::StopLocationUpdates()
                {
                	ASSERT_NATIVE_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID stopUpdatingLocation = env->GetMethodID(m_locationManagerClass,
																	  "stopUpdatingLocation",
																	  "()V");
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                    Eegeo_ASSERT(stopUpdatingLocation != nullptr);

					env->CallVoidMethod(m_locationManagerInstance, stopUpdatingLocation);
                    Eegeo_ASSERT(env->ExceptionCheck() == JNI_FALSE);
                }
            }
        }
    }
}
