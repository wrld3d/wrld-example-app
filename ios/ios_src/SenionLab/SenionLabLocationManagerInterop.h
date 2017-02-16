// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <map>
#include <string>

#include "ISenionLabLocationManager.h"
#include "SenionLabLocationManager.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationManagerInterop : public InteriorsPosition::SdkModel::SenionLab::ISenionLabLocationManager, protected Eegeo::NonCopyable
        {
        public:
            SenionLabLocationManagerInterop(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& senionLabLocationService,
                                            Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& alertBoxFactory,
                                            ExampleAppMessaging::TMessageBus& messageBus);
            ~SenionLabLocationManagerInterop();
            void StartUpdatingLocation(const std::string& apiKey,
                                       const std::string& apiSecret,
                                       const std::map<int, std::string>& floorMap);
            void StopUpdatingLocation();
            
        private:
            SenionLabLocationManager* m_pImpl;
        };
    }
}
