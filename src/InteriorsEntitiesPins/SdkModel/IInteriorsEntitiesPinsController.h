// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "CallbackCollection.h"
#include "AppInterface.h"
#include <vector>
#include "Pin.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            class IInteriorsEntitiesPinsController
            {
            public:
                virtual ~IInteriorsEntitiesPinsController()
                {
                    
                }
                
                virtual void Update(float dt) = 0;

                virtual void Event_TouchTap(const AppInterface::TapData& data) = 0;

                virtual void RegisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback) = 0;
                virtual void UnregisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback) = 0;
            };
        }
    }
}