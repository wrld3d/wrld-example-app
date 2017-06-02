// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <map>
#include <string>

#include "IIndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationService.h"
#include "IndoorAtlasLocationManagerObjC.h"
#include "iOSAlertBoxFactory.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationManager : public IIndoorAtlasLocationManager, protected Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationManager(IndoorAtlas::IndoorAtlasLocationService* indoorAtlasLocationService,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& iOSAlertBoxFactory);
                    ~IndoorAtlasLocationManager();
                    
                    void StartUpdatingLocation(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap);
                    void StopUpdatingLocation();
                    
                private:
                    IndoorAtlasLocationManagerObjC* m_pLocationManager;
                };
            }
        }
    }
}
