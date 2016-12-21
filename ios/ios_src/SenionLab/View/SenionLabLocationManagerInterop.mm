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
            {
            
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
                m_messageBus.Publish(ExampleApp::IndoorLocation::IndoorLocationChangedMessage(location));
                m_messageBus.FlushToNative();
            }
            
            void SenionLabLocationManagerInterop::SetIsAuthorized(bool isAuthorize)
            {
                m_pSenionLabLocationService->SetIsAuthorized(isAuthorize);
            }
            
            void SenionLabLocationManagerInterop::OnSetFloorIndex(int floorIndex)
            {
                m_pSenionLabLocationService->SetFloorIndex(floorIndex);
            }
        }
    }
}

