// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinVisibilityStateChangedHandlerFactory
            {
            public:
                virtual ~IMyPinVisibilityStateChangedHandlerFactory() {}
                
                virtual WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* CreateMyPinVisibilityStateChangedHandler(MyPinModel& myPinModel) const = 0;
            };
        }
    }
}
