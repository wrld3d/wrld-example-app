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
            IndoorAtlasLocationManagerInterop::IndoorAtlasLocationManagerInterop(IndoorAtlasLocationManager* pIndoorAtlasLocationManager,
                                                                                 ExampleApp::IndoorAtlas::IndoorAtlasLocationService* pIndoorAtlasLocationService,
                                                                                 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
            : m_pIndoorAtlasLocationManager(pIndoorAtlasLocationManager)
            , m_pIndoorAtlasLocationService(pIndoorAtlasLocationService)
            , m_messageBus(messageBus)
            , m_startUpdatingLocationCallback(this, &IndoorAtlasLocationManagerInterop::OnStartUpdatingLocation)
            , m_stopUpdatingLocationCallback(this, &IndoorAtlasLocationManagerInterop::OnStopUpdatingLocation)
            , m_floorIndexChangedCallback(this, &IndoorAtlasLocationManagerInterop::OnFloorIndexChanged)
            {
                m_messageBus.SubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.SubscribeUi(m_stopUpdatingLocationCallback);
                m_messageBus.SubscribeUi(m_floorIndexChangedCallback);
            }
            
            IndoorAtlasLocationManagerInterop::~IndoorAtlasLocationManagerInterop()
            {
                m_messageBus.UnsubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.UnsubscribeUi(m_stopUpdatingLocationCallback);
                m_messageBus.UnsubscribeUi(m_floorIndexChangedCallback);
            }
            
            void IndoorAtlasLocationManagerInterop::StartUpdatingLocation(const std::string apiKey,
                                                                          const std::string apiSecret,
                                                                          const std::map<int, std::string> floorMap,
                                                                          const int floorIndex)
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
                m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionLocationChangedMessage(location));
            }
            
            void IndoorAtlasLocationManagerInterop::OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage)
            {
                StartUpdatingLocation(startUpdatingLocationMessage.GetApiKey(),
                                      startUpdatingLocationMessage.GetApiSecret(),
                                      startUpdatingLocationMessage.GetFloorMap(),
                                      startUpdatingLocationMessage.GetCurrentFloorIndex());
            }
            
            void IndoorAtlasLocationManagerInterop::OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage)
            {
                StopUpdatingLocation();
            }
            
            void IndoorAtlasLocationManagerInterop::OnFloorIndexChanged(const ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage& floorChangedMessage)
            {
                SetFloorIndex(floorChangedMessage.GetFloorIndex());
            }
        }
    }
}

