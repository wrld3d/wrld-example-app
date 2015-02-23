// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            void Apply(IScreenControlViewModel& viewModel, IScreenControlView& view);
        }
    }
}
