// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class IDirectionsMenuInitiationViewModel : public ScreenControl::View::IScreenControlViewModel
            {
            public:

                virtual ~IDirectionsMenuInitiationViewModel() { }

                virtual bool ShouldOffsetViewButton() const = 0;
                virtual void SetShouldOffsetViewButton(bool shouldOffset) = 0;
            };
        }
    }
}
