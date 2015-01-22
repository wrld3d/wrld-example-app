// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinDetails.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            class IMyPinDetailsModule
            {
            public:
                virtual ~IMyPinDetailsModule() { }

                virtual MyPinDetails::View::IMyPinDetailsViewModel& GetMyPinDetailsViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
