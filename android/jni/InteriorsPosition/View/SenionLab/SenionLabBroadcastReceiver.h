// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "SenionLabLocationInterop.h"
#include "SenionLabLocationService.h"

#include <jni.h>
#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace View
        {
            namespace SenionLab
            {
                class SenionLabBroadcastReceiver : private Eegeo::NonCopyable
                {
                public:
                    SenionLabBroadcastReceiver(SdkModel::SenionLab::SenionLabLocationInterop& locationmanager,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               AndroidNativeState& nativeState);
                    ~SenionLabBroadcastReceiver();

                    void RegisterReceiver();
                    void UnregisterReceiver();

                    void DidUpdateLocation(
                            const double latitudeInDegrees,
                            const double longitudeInDegrees,
                            const double horizontalAccuracyInMeters,
                            const int senionFloorNumber);

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
