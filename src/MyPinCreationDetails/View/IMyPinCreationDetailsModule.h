// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreationDetails.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class IMyPinCreationDetailsModule
            {
            public:
                virtual ~IMyPinCreationDetailsModule() { }

                virtual IMyPinCreationDetailsViewModel& GetMyPinCreationDetailsViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
