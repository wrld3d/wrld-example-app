//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IndoorAtlasLocationManagerInterop.h"
#include "IndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationService.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        namespace View
        {
            IndoorAtlasLocationManagerInterop::IndoorAtlasLocationManagerInterop(IndoorAtlasLocationManager* indoorAtlasLocationManager,
                                                                                 ExampleApp::IndoorAtlas::IndoorAtlasLocationService* pIndoorAtlasLocationService,
                                                                                 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
            : m_pIndoorAtlasLocationManager(indoorAtlasLocationManager)
            , m_pIndoorAtlasLocationService(pIndoorAtlasLocationService)
            , m_messageBus(messageBus)
            {
            
            }
            
            void IndoorAtlasLocationManagerInterop::StartUpdatingLocation(std::string apiKey,
                                                                          std::string apiSecret,
                                                                          std::map<int, std::string> floorMap,
                                                                          int floorIndex)
            {
                [m_pIndoorAtlasLocationManager StartUpdatingLocation:[NSString stringWithFormat:@"%s", apiKey.c_str()] apiSecret:[NSString stringWithFormat:@"%s",apiSecret.c_str()]  floorMap:floorMap floorIndex:floorIndex];
            }
            
            void IndoorAtlasLocationManagerInterop::StopUpdatingLocation()
            {
                [m_pIndoorAtlasLocationManager StopUpdatingLocation];
            }
            
            void IndoorAtlasLocationManagerInterop::SetFloorIndex(int floorIndex)
            {
                [m_pIndoorAtlasLocationManager SetFloorIndex: floorIndex];
            }
            
            void IndoorAtlasLocationManagerInterop::OnSetFloorIndex(int floorIndex)
            {
                m_pIndoorAtlasLocationService->SetFloorIndex(floorIndex);
            }
            
            void IndoorAtlasLocationManagerInterop::OnLocationChanged(Eegeo::Space::LatLong& location)
            {
                m_messageBus.Publish(ExampleApp::IndoorLocation::IndoorLocationChangedMessage(location));
                m_messageBus.FlushToNative();
            }
        }
    }
}

