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
#include "IIndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationManager : public IIndoorAtlasLocationManager, protected Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationManager(IndoorAtlas::IndoorAtlasLocationService& indoorAtlasLocationService,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               AndroidNativeState& nativeState);
                    ~IndoorAtlasLocationManager();

                    void StartUpdatingLocation(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap);
                    void StopUpdatingLocation();

                    void DidUpdateLocation(const double latitude, const double longitude, const std::string& floorId);
                    void SetIsAuthorized(const bool isAuthorized);

                    void OnDidUpdateLocation(const InteriorsLocationChangedMessage& message);
                    void OnSetIsAuthorized(const InteriorsLocationAuthorizationChangedMessage& message);

                private:
                    bool TryMapFloorIdToFloorIndex(const std::string floorId, int& wrldFloorId);

                    AndroidNativeState& m_nativeState;
                    IndoorAtlasLocationService& m_indoorAtlasLocationService;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    Eegeo::Helpers::TCallback1<IndoorAtlasLocationManager, const InteriorsLocationChangedMessage&> m_onDidUpdateLocationCallback;
                    Eegeo::Helpers::TCallback1<IndoorAtlasLocationManager, const InteriorsLocationAuthorizationChangedMessage&> m_onSetIsAuthorized;
                    jclass m_locationManagerClass;
                    jobject m_locationManagerInstance;
                    std::map<int, std::string> m_floorMap;
                };
            }
        }
    }
}
