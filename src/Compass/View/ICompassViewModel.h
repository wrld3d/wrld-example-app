// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class ICompassViewModel : public ScreenControl::View::IScreenControlViewModel
            {
            public:
                virtual ~ICompassViewModel() { }
            };
        }
    }
}
