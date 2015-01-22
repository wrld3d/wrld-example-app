// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "Camera.h"
#include "ScreenControlViewModelIncludes.h"
#include "VectorMathDecl.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class IMyPinCreationModule
            {
            public:
                virtual ~IMyPinCreationModule() {}

                virtual IMyPinCreationModel& GetMyPinCreationModel() const = 0;
                virtual View::IMyPinCreationInitiationViewModel& GetMyPinCreationInitiationViewModel() const = 0;
                virtual View::IMyPinCreationConfirmationViewModel& GetMyPinCreationConfirmationViewModel() const = 0;
                virtual View::IMyPinCreationCompositeViewModel& GetMyPinCreationCompositeViewModel() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetInitiationScreenControlViewModel() const = 0;
                virtual ScreenControl::View::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
