// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "Types.h"
#include "IndoorAtlasLocationIncludes.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "InteriorsPositionFloorChangedMessage.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "LatLongAltitude.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        namespace View {
            
            class IndoorAtlasLocationManagerInterop: private Eegeo::NonCopyable
            {
            private:
                IndoorAtlasLocationManager* m_pIndoorAtlasLocationManager;
                ExampleApp::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
                ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            public:
                IndoorAtlasLocationManagerInterop(IndoorAtlasLocationManager* pIndoorAtlasLocationManager,
                                                  ExampleApp::IndoorAtlas::IndoorAtlasLocationService* pIndoorAtlasLocationService,
                                                  ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~IndoorAtlasLocationManagerInterop();
                
                virtual void StartUpdatingLocation(const std::string apiKey,
                                                   const std::string apiSecret,
                                                   const std::map<int, std::string> floorMap,
                                                   const int floorIndex);
                
                virtual void StopUpdatingLocation();
                virtual void SetFloorIndex(int floorIndex);
                
                void OnSetFloorIndex(int floorIndex);
                void OnLocationChanged(Eegeo::Space::LatLong& location);
                
                void OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage);
                void OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage);
                void OnFloorIndexChanged(const ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage& floorChangedMessage);
                
                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManagerInterop, const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage&> m_startUpdatingLocationCallback;
                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManagerInterop, const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage&> m_stopUpdatingLocationCallback;
                Eegeo::Helpers::TCallback1<IndoorAtlasLocationManagerInterop, const ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage&> m_floorIndexChangedCallback;
            };
        }
    }
}

