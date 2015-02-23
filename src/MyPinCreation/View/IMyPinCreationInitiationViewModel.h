// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationInitiationViewModel : public ScreenControl::View::IScreenControlViewModel
            {
            public:

                virtual ~IMyPinCreationInitiationViewModel() { }

                virtual bool ShouldOffsetViewButton() const = 0;
                virtual void SetShouldOffsetViewButton(bool shouldOffset) = 0;
            };
        }
    }
}
