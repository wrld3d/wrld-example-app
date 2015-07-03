// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsEntitiesPins.h"
#include "Pin.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            class IInteriorsEntitiesPinsModule
            {
            public:
                virtual IInteriorsEntitiesPinsController& GetInteriorsEntitiesPinsController() = 0;
                virtual Eegeo::Pins::PinsModule& GetPinsModule() = 0;
                virtual ~IInteriorsEntitiesPinsModule(){}
            };
        }
    }
}