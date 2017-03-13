// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>
#include <map>
#include <string>

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "SenionLabLocationManager.h"
#include "SenionLabLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace View
        {
            namespace SenionLab
            {
                class SenionLabBroadcastReceiver : protected Eegeo::NonCopyable
                {
                public:
                    SenionLabBroadcastReceiver(SdkModel::SenionLab::SenionLabLocationManager& locationmanager,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               AndroidNativeState& nativeState);
                    ~SenionLabBroadcastReceiver();

                    void RegisterReceiver();
                    void UnregisterReceiver();

                    void DidUpdateLocation(const double latitude, const double longitude, const int floorNumber);
                    void SetIsAuthorized(const bool isAuthorized);

                private:
                    AndroidNativeState& m_nativeState;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    jclass m_broadcastReceiverClass;
                    jobject m_broadcastReceiverInstance;
                };
            }
        }
    }
}
