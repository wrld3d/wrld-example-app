// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "Types.h"
#include "SenionLabLocationIncludes.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "LatLongAltitude.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace SenionLab
    {
        namespace View {
            
            class SenionLabLocationManagerInterop: private Eegeo::NonCopyable
            {
            private:
                SenionLabLocationManager* m_pSenionLabLocationManager;
                ExampleApp::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
                ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            public:
                SenionLabLocationManagerInterop(SenionLabLocationManager* senionLabLocationManager,
                                                  ExampleApp::SenionLab::SenionLabLocationService* pSenionLabLocationService,
                                                  ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~SenionLabLocationManagerInterop();
                
                virtual void StartUpdatingLocation(std::string apiKey,
                                                   std::string apiSecret,
                                                   std::map<int, std::string> floorMap);
                virtual void StopUpdatingLocation();
                
                void OnLocationChanged(Eegeo::Space::LatLong& location);
                void SetIsAuthorized(bool isAuthorize);
                void OnSetFloorIndex(int floorIndex);
                
                void OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage);
                void OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage);
                
                Eegeo::Helpers::TCallback1<SenionLabLocationManagerInterop, const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage&> m_startUpdatingLocationCallback;
                Eegeo::Helpers::TCallback1<SenionLabLocationManagerInterop, const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage&> m_stopUpdatingLocationCallback;
            };
        }
    }
}

