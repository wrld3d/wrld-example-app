//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SenionLabLocationManagerInterop.h"
#include "SenionLabLocationManager.h"
#include "SenionLabLocationService.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        namespace View
        {
            SenionLabLocationManagerInterop::SenionLabLocationManagerInterop(SenionLabLocationManager* senionLabLocationManager,
                                                                                 ExampleApp::SenionLab::SenionLabLocationService* pSenionLabLocationService,
                                                                                 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
            : m_pSenionLabLocationManager(senionLabLocationManager)
            , m_pSenionLabLocationService(pSenionLabLocationService)
            , m_messageBus(messageBus)
            , m_startUpdatingLocationCallback(this, &SenionLabLocationManagerInterop::OnStartUpdatingLocation)
            , m_stopUpdatingLocationCallback(this, &SenionLabLocationManagerInterop::OnStopUpdatingLocation)
            {
                m_messageBus.SubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.SubscribeUi(m_stopUpdatingLocationCallback);
            }
            
            SenionLabLocationManagerInterop::~SenionLabLocationManagerInterop()
            {
                m_messageBus.UnsubscribeUi(m_startUpdatingLocationCallback);
                m_messageBus.UnsubscribeUi(m_stopUpdatingLocationCallback);
            }
            
            void SenionLabLocationManagerInterop::StartUpdatingLocation(std::string apiKey,
                                                                        std::string apiSecret,
                                                                        std::map<int, std::string> floorMap)
            {
                [m_pSenionLabLocationManager StartUpdatingLocation:[NSString stringWithFormat:@"%s", apiKey.c_str()] apiSecret:[NSString stringWithFormat:@"%s",apiSecret.c_str()]  floorMap:floorMap];
            }
            
            void SenionLabLocationManagerInterop::StopUpdatingLocation()
            {
                [m_pSenionLabLocationManager StopUpdatingLocation];
            }
            
            void SenionLabLocationManagerInterop::OnLocationChanged(Eegeo::Space::LatLong& location)
            {
                m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionLocationChangedMessage(location));
            }
            
            void SenionLabLocationManagerInterop::SetIsAuthorized(bool isAuthorize)
            {
                m_pSenionLabLocationService->SetIsAuthorized(isAuthorize);
            }
            
            void SenionLabLocationManagerInterop::OnSetFloorIndex(int floorIndex)
            {
                m_pSenionLabLocationService->SetFloorIndex(floorIndex);
            }
            
            void SenionLabLocationManagerInterop::OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage)
            {
                StartUpdatingLocation(startUpdatingLocationMessage.GetApiKey(),
                                      startUpdatingLocationMessage.GetApiSecret(),
                                      startUpdatingLocationMessage.GetFloorMap());
            }
            
            void SenionLabLocationManagerInterop::OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage)
            {
                StopUpdatingLocation();
            }
        }
    }
}

