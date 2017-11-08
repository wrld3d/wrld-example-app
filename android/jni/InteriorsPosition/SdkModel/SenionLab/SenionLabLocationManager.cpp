// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>
#include <map>
#include <sstream>
#include <vector>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "ApplicationConfiguration.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "InteriorsHeadingChangedMessage.h"
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
                , m_onDidUpdateHeadingCallback(this, &SenionLabLocationManager::OnDidUpdateHeading)
                , m_onSetIsAuthorized(this, &SenionLabLocationManager::OnSetIsAuthorized)
                , m_onSetInteriorIdFromMapKey(this, &SenionLabLocationManager::OnSetInteriorIdFromMapKey)
                , m_onSetIsConnected(this, &SenionLabLocationManager::OnSetIsConnected)
                , m_isActive(false)
                {
                    ASSERT_NATIVE_THREAD

                    m_messageBus.SubscribeNative(m_onDidUpdateLocationCallback);
                    m_messageBus.SubscribeNative(m_onDidUpdateHeadingCallback);
                    m_messageBus.SubscribeNative(m_onSetIsAuthorized);
                    m_messageBus.SubscribeNative(m_onSetInteriorIdFromMapKey);
                    m_messageBus.SubscribeNative(m_onSetIsConnected);

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

                    m_messageBus.UnsubscribeNative(m_onSetIsConnected);
                    m_messageBus.UnsubscribeNative(m_onSetInteriorIdFromMapKey);
                    m_messageBus.UnsubscribeNative(m_onSetIsAuthorized);
                    m_messageBus.UnsubscribeNative(m_onDidUpdateHeadingCallback);
                    m_messageBus.UnsubscribeNative(m_onDidUpdateLocationCallback);

                    AndroidSafeNativeThreadAttachment attached(m_nativeState);
                    JNIEnv* env = attached.envForThread;

                    env->DeleteGlobalRef(m_locationManagerInstance);
                    env->DeleteGlobalRef(m_locationManagerClass);
                }

                void SenionLabLocationManager::StartUpdatingLocation(const std::string& apiSecret,
                                                                     const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& senionInfoMap,
                                                                     const std::map<std::string, std::map<int, std::vector<std::string> > >& floorMaps,
                                                                     const std::map<std::string, Eegeo::Resources::Interiors::InteriorId>& interiorIds)
                {
                    m_floorMaps = floorMaps;
                    m_interiorIds = interiorIds;
                    m_mapKey = "";
                    m_customerId = apiSecret;
                    m_isActive = true;

                    for(auto &it : senionInfoMap)
                    {
                        m_mapKeyVector.push_back(it.second.GetConfig().GetApiKey().c_str());
                    }

                    AskUserToEnableBluetoothIfDisabled();
                    StartLocationUpdates();
                }

                void SenionLabLocationManager::StopUpdatingLocation()
                {
                    m_isActive = false;
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
                    int floorIndex = FloorIdToFloorIndex(m_mapKey, message.FloorId());
                    m_senionLabLocationService.SetFloorIndex(floorIndex);

                    m_messageBus.Publish(ExampleApp::AboutPage::AboutPageSenionDataTypeMessage(floorIndex, message.FloorId(), message.Latitude(), message.Longitude()));
                }

                void SenionLabLocationManager::OnDidUpdateHeading(const InteriorsHeadingChangedMessage& message)
                {
                    m_senionLabLocationService.SetHeadingDegrees(message.HeadingDegrees());
                }

                void SenionLabLocationManager::OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message)
                {
                    m_senionLabLocationService.SetIsAuthorized(message.IsAuthorized());
                }

                void SenionLabLocationManager::OnSetInteriorIdFromMapKey(const InteriorsLocationMapKeyChangedMessage& message)
                {
                    m_mapKey = message.MapKey();
                    std::map<std::string, Eegeo::Resources::Interiors::InteriorId>::iterator it = m_interiorIds.find(m_mapKey);

                    if(it != m_interiorIds.end())
                    {
                        m_senionLabLocationService.SetInteriorId(it->second);

                        std::map<std::string, std::map<int, std::vector<std::string> > >::iterator floor_it = m_floorMaps.find(m_mapKey);
                        if(floor_it != m_floorMaps.end())
                        {
                            m_messageBus.Publish(ExampleApp::AboutPage::AboutPageSenionSettingsTypeMessage(m_mapKey, m_customerId, floor_it->second, it->second.Value()));
                        }
                    }
                }

                void SenionLabLocationManager::OnSetIsConnected(const InteriorsLocationConnectionChangedMessage& message)
                {
                	m_senionLabLocationService.SetIsConnected(message.IsConnected());

                	if(message.IsConnected())
                	{
                		m_messageBus.Publish(ExampleApp::AboutPage::AboutPageIndoorPositionTypeMessage("\nIndoor positioning type: Senion"));
                	}
                	else
                	{
                		m_messageBus.Publish(ExampleApp::AboutPage::AboutPageIndoorPositionTypeMessage("\nIndoor positioning type: GPS"));
                	}
                }

                int SenionLabLocationManager::FloorIdToFloorIndex(const std::string& mapKey, const std::string& floorId)
                {
                    std::map<std::string, std::map<int, std::vector<std::string> > >::iterator mapKey_it = m_floorMaps.find(mapKey);

                	if(mapKey_it != m_floorMaps.end())
                	{
                        for(std::map<int, std::vector<std::string> >::iterator floor_it = mapKey_it->second.begin(); floor_it != mapKey_it->second.end(); ++floor_it)
                        {
                            for (std::vector<std::string>::iterator possible_target_it = floor_it->second.begin();
                                 possible_target_it != floor_it->second.end();
                                 ++possible_target_it)
                            {
                                if (*possible_target_it == floorId)
                                {
                                    return floor_it->first;
                                }
                            }
                        }
                	}

                    return -1;
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
                                                                       "([Ljava/lang/String;Ljava/lang/String;)V");

                    jobjectArray mapKeyJObjectArray = env->NewObjectArray(m_mapKeyVector.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));

                    for(int i = 0; i < m_mapKeyVector.size(); ++i)
                    {
                        env->SetObjectArrayElement(mapKeyJObjectArray, i, env->NewStringUTF(m_mapKeyVector[i].c_str()));
                    }

                    jstring customerIdJString = env->NewStringUTF(m_customerId.c_str());
                    env->CallVoidMethod(m_locationManagerInstance,
                                        startUpdatingLocation,
                                        mapKeyJObjectArray,
                                        customerIdJString);
                    env->DeleteLocalRef(mapKeyJObjectArray);
                    env->DeleteLocalRef(customerIdJString);
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
