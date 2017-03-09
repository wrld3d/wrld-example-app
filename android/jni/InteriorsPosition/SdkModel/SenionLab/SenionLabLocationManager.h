// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>
#include <map>
#include <string>

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
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

                    void StartUpdatingLocation(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap);
                    void StopUpdatingLocation();

                    jobject ManagedInstance() const;

                    void OnDidUpdateLocation(const InteriorsLocationChangedMessage& message);
                    void OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message);

                    void OnResume();
                    void OnPause();

                private:
                    int FloorNumberToFloorIndex(const int floorIndex);

                    void AskUserToEnableBluetoothIfDisabled();
                    void StartLocationUpdates();
                    void StopLocationUpdates();

                    AndroidNativeState& m_nativeState;
                    SenionLabLocationService& m_senionLabLocationService;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationChangedMessage&> m_onDidUpdateLocationCallback;
                    Eegeo::Helpers::TCallback1<SenionLabLocationManager, const InteriorsLocationAuthorizationChangedMessage&> m_onSetIsAuthorized;
                    jclass m_locationManagerClass;
                    jobject m_locationManagerInstance;
                    std::map<int, std::string> m_floorMap;

                    std::string m_apiKey;
                    std::string m_apiSecret;
                    bool m_isActive;
                };
            }
        }
    }
}
