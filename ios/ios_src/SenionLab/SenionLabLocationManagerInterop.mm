// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationManager.h"
#include "SenionLabLocationManagerInterop.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationManagerInterop::SenionLabLocationManagerInterop(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& senionLabLocationService,
                                                                         Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& alertBoxFactory,
                                                                         ExampleAppMessaging::TMessageBus& messageBus)
        : m_pImpl([[SenionLabLocationManager alloc] Init: &senionLabLocationService
                                      iOSAlertBoxFactory: &alertBoxFactory
                                              messageBus: &messageBus])
        {
        }
        
        SenionLabLocationManagerInterop::~SenionLabLocationManagerInterop()
        {
            [m_pImpl release];
            m_pImpl = nullptr;
        }
        
        void SenionLabLocationManagerInterop::StartUpdatingLocation(const std::string& apiKey,
                                                                    const std::string& apiSecret,
                                                                    const std::map<int, std::string>& floorMap)
        {
            [m_pImpl StartUpdatingLocation: [NSString stringWithUTF8String:apiKey.c_str()]
                                 apiSecret: [NSString stringWithUTF8String:apiSecret.c_str()]
                                  floorMap: floorMap];
        }
        
        void SenionLabLocationManagerInterop::StopUpdatingLocation()
        {
            [m_pImpl StopUpdatingLocation];
        }
    }
}
