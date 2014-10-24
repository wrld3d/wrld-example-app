// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class IMyPinsModule
        {
        public:
            virtual ~IMyPinsModule() { }
            virtual IMyPinsService& GetMyPinsService() const = 0;
        };
    }
}