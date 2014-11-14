// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "Camera.h"
#include "ScreenControlViewModelIncludes.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationModule
        {
        public:
            virtual ~IMyPinCreationModule(){}
            
            virtual IMyPinCreationModel& GetMyPinCreationModel() const = 0;
            virtual IMyPinCreationInitiationViewModel& GetMyPinCreationInitiationViewModel() const = 0;
            virtual IMyPinCreationConfirmationViewModel& GetMyPinCreationConfirmationViewModel() const = 0;
            virtual IMyPinCreationCompositeViewModel& GetMyPinCreationCompositeViewModel() const = 0;
            
            virtual ScreenControlViewModel::IScreenControlViewModel& GetInitiationScreenControlViewModel() const = 0;
            virtual ScreenControlViewModel::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const = 0;
        };
    }
}