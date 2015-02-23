// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class IMyPinDetailsDisplayService
            {
            public:
                virtual ~IMyPinDetailsDisplayService() { }
                
                virtual void DisplayPinDetails(const MyPins::SdkModel::MyPinModel& myPinModel) = 0;
            };
        }
    }
}
