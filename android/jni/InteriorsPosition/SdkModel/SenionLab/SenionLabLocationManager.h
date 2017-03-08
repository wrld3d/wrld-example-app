// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>
#include <map>
#include <string>
#include <vector>

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "InteriorsLocationMapKeyChangedMessage.h"
#include "InteriorsLocationConnectionChangedMessage.h"
#include "ISenionLabLocationManager.h"
#include "SenionLabLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationManager : public ISenionLabLocationManager, protected Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationManager(SenionLab::SenionLabLocationService& senionLabLocationService,
                                             ExampleAppMessaging::TMessageBus& messageBus,
                                             AndroidNativeState& nativeState);
                    ~SenionLabLocationManager();

                    void StartUpdatingLocation(const std::string& apiSecret,
                                               const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& senionInfoMap,
                                               const std::map<std::string, std::map<int, std::string> >& floorMaps,
                                               const std::map<std::string, Eegeo::Resources::Interiors::InteriorId>& interiorIds);
                    void StopUpdatingLocation();

                    jobject ManagedInstance() const;

                    void OnDidUpdateLocation(const InteriorsLocationChangedMessage& message);
                    void OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message);
                    void OnSetInteriorIdFromMapKey(const InteriorsLocationMapKeyChangedMessage& message);
                    void OnSetIsConnected(const InteriorsLocationConnectionChangedMessage& message);

                    void OnResume();
                    void OnPause();

                private:
                    int FloorNumberToFloorIndex(const std::string& mapKey, const int floorIndex);

                    void AskUserToEnableBluetoothIfDisabled();
                    void StartLocationUpdates();
                    void StopLocationUpdates();

                    AndroidNativeState& m_nativeState;
                    SenionLabLocationService& m_senionLabLocationService;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationChangedMessage&> m_onDidUpdateLocationCallback;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationAuthorizationChangedMessage&> m_onSetIsAuthorized;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationMapKeyChangedMessage&> m_onSetInteriorIdFromMapKey;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationConnectionChangedMessage&> m_onSetIsConnected;
                    jclass m_locationManagerClass;
                    jobject m_locationManagerInstance;
                    std::map<std::string, std::map<int, std::string>> m_floorMaps;
                    std::map<std::string, Eegeo::Resources::Interiors::InteriorId> m_interiorIds;
                    std::string m_mapKey;
                    std::string m_customerId;
                    std::vector<std::string> m_mapKeyVector;
                    bool m_isActive;
                };
            }
        }
    }
}
