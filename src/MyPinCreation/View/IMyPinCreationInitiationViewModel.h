// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationInitiationViewModel : public ScreenControlViewModel::IScreenControlViewModel
        {
        public:
            
            virtual ~IMyPinCreationInitiationViewModel() { }
            
            virtual bool ShouldOffsetViewButton() const = 0;
            virtual void SetShouldOffsetViewButton(bool shouldOffset) = 0;
        };
    }
}
