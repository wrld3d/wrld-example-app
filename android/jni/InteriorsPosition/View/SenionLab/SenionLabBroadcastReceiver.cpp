// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "SenionLabLocationService.h"
#include "SenionLabBroadcastReceiver.h"
#include "SenionLabLocationManager.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace View
        {
            namespace SenionLab
            {
                SenionLabBroadcastReceiver::SenionLabBroadcastReceiver(SdkModel::SenionLab::SenionLabLocationManager& locationManager,
                                                                       ExampleAppMessaging::TMessageBus &messageBus,
                                                                       AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
                {
                    ASSERT_UI_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    jstring broadcastReceiverClassName = env->NewStringUTF("com/eegeo/interiorsposition/senionlab/SenionLabBroadcastReceiver");
                    jclass broadcastReceiverClass = m_nativeState.LoadClass(env, broadcastReceiverClassName);
                    env->DeleteLocalRef(broadcastReceiverClassName);

                    m_broadcastReceiverClass = static_cast<jclass>(env->NewGlobalRef(broadcastReceiverClass));
                    jmethodID broadcastReceiverInit = env->GetMethodID(m_broadcastReceiverClass, "<init>", "(Lcom/eegeo/interiorsposition/senionlab/SenionLabLocationManager;J)V");

                    jobject instance = env->NewObject(m_broadcastReceiverClass,
                                                      broadcastReceiverInit,
                                                      locationManager.ManagedInstance(),
                                                      reinterpret_cast<jlong>(this));
                    m_broadcastReceiverInstance = env->NewGlobalRef(instance);
                }

                SenionLabBroadcastReceiver::~SenionLabBroadcastReceiver()
                {
                    ASSERT_UI_THREAD

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_broadcastReceiverInstance);
                    env->DeleteGlobalRef(m_broadcastReceiverClass);
                }

                void SenionLabBroadcastReceiver::RegisterReceiver()
                {
                	AndroidSafeNativeThreadAttachment attached(m_nativeState);
                	JNIEnv* env = attached.envForThread;

                	jmethodID registerMethod = env->GetMethodID(m_broadcastReceiverClass, "registerReceiver", "()V");
                	env->CallVoidMethod(m_broadcastReceiverInstance, registerMethod);
                }

                void SenionLabBroadcastReceiver::UnregisterReceiver()
				{
                	AndroidSafeNativeThreadAttachment attached(m_nativeState);
                	JNIEnv* env = attached.envForThread;

                	jmethodID unregisterMethod = env->GetMethodID(m_broadcastReceiverClass, "unregisterReceiver", "()V");
                	env->CallVoidMethod(m_broadcastReceiverInstance, unregisterMethod);
				}

                void SenionLabBroadcastReceiver::DidUpdateLocation(const double latitude, const double longitude, const int floorNumber)
                {
                    ASSERT_UI_THREAD
                    Eegeo::Space::LatLong location(Eegeo::Space::LatLong::FromDegrees(latitude, longitude));
                    m_messageBus.Publish(InteriorsLocationChangedMessage(latitude, longitude, floorNumber));
                }

                void SenionLabBroadcastReceiver::SetIsAuthorized(const bool isAuthorized)
                {
                    ASSERT_UI_THREAD
                    m_messageBus.Publish(InteriorsLocationAuthorizationChangedMessage(isAuthorized));
                }
            }
        }
    }
}
