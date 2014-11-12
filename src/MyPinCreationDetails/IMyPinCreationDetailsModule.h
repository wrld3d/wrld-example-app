// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationDetails.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class IMyPinCreationDetailsModule
        {
        public:
            ~IMyPinCreationDetailsModule(){ }
            
            virtual IMyPinCreationDetailsViewModel& GetMyPinCreationDetailsViewModel() const = 0;
            
            virtual OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
        };
    }
}