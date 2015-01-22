// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinSelectionHandlerFactory
            {
            public:
                virtual ~IMyPinSelectionHandlerFactory() {}
                virtual MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const = 0;
            };
        }
    }
}
