// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "Types.h"
#include "ISenionLabLocationManager.h"
#include "SenionLabLocationIncludes.h"
#include "BidirectionalBus.h"
#include "LatLongAltitude.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace SenionLab
    {
        namespace View {
            
            class SenionLabLocationManagerInterop: public ISenionLabLocationManager, private Eegeo::NonCopyable
            {
            private:
                SenionLabLocationManager* m_pSenionLabLocationManager;
                ExampleApp::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
                ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            public:
                SenionLabLocationManagerInterop(SenionLabLocationManager* senionLabLocationManager,
                                                  ExampleApp::SenionLab::SenionLabLocationService* pSenionLabLocationService,
                                                  ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~SenionLabLocationManagerInterop() {}
                
                virtual void StartUpdatingLocation(std::string apiKey,
                                                   std::string apiSecret,
                                                   std::map<int, std::string> floorMap);
                
                virtual void StopUpdatingLocation();
                void OnLocationChanged(Eegeo::Space::LatLong& location);
                void SetIsAuthorized(bool isAuthorize);
                void OnSetFloorIndex(int floorIndex);
            };
        }
    }
}

