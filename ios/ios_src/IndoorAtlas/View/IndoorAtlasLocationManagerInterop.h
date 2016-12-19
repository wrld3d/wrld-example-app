// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "Types.h"
#include "IIndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationIncludes.h"
#include "BidirectionalBus.h"
#include "LatLongAltitude.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        namespace View {
            
            class IndoorAtlasLocationManagerInterop: public IIndoorAtlasLocationManager, private Eegeo::NonCopyable
            {
            private:
                IndoorAtlasLocationManager* m_pIndoorAtlasLocationManager;
                ExampleApp::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
                ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            public:
                IndoorAtlasLocationManagerInterop(IndoorAtlasLocationManager* indoorAtlasLocationManager,
                                                  ExampleApp::IndoorAtlas::IndoorAtlasLocationService* pIndoorAtlasLocationService,
                                                  ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~IndoorAtlasLocationManagerInterop() {}
                
                virtual void StartUpdatingLocation(std::string apiKey,
                                                   std::string apiSecret,
                                                   std::map<int, std::string> floorMap,
                                                   int floorIndex);
                
                virtual void StopUpdatingLocation();
                virtual void SetFloorIndex(int floorIndex);
                
                void OnSetFloorIndex(int floorIndex);
                void OnLocationChanged(Eegeo::Space::LatLong& location);
            };
        }
    }
}

