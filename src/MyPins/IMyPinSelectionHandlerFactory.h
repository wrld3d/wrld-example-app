// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class IMyPinSelectionHandlerFactory
        {
        public:
            virtual ~IMyPinSelectionHandlerFactory() {}
            virtual MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const = 0;
        };
    }
}