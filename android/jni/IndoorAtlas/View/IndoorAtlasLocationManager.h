// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "IndoorAtlasLocationService.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "InteriorsPositionFloorChangedMessage.h"
#include "ICallback.h"
#include <string>
#include <map>
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        namespace View
        {
            class IndoorAtlasLocationManager : private Eegeo::NonCopyable
            {
            private:
                ExampleApp::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
                std::map<int, std::string> m_floorMap;
                int m_floorIndex;

                AndroidNativeState& m_nativeState;
                jclass m_jniApiClass;
                jobject m_jniApiInstance;
                ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;

                std::string GetFloorPlanIdFromFloorIndex(int floorIndex);

            public:
                IndoorAtlasLocationManager(ExampleApp::IndoorAtlas::IndoorAtlasLocationService* pIndoorAtlasLocationService,
                                           AndroidNativeState& nativeState,
                                           ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
                virtual ~IndoorAtlasLocationManager();

                void StartUpdatingLocation(const std::string apiKey,
                                           const std::string apiSecret,
                                           const std::map<int, std::string> floorMap,
                                           const int floorIndex);

                void StopUpdatingLocation();
                void SetFloorIndex(int floorIndex);
                void OnUpdateLocation(double latitude, double longitude);

                void OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage);
                void OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage);
                void OnFloorIndexChanged(const ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage& floorChangedMessage);

                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManager, const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage&> m_startUpdatingLocationCallback;
                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManager, const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage&> m_stopUpdatingLocationCallback;
                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManager, const ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage&> m_floorIndexChangedCallback;
            };
        }
    }
}

