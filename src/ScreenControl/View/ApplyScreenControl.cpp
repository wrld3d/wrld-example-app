// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplyScreenControl.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            void Apply(IScreenControlViewModel& viewModel, IScreenControlView& view)
            {
                if (viewModel.IsFullyOffScreen())
                {
                    view.SetFullyOffScreen();
                }
                else if (viewModel.IsFullyOnScreen())
                {
                    view.SetFullyOnScreen();
                }
                else
                {
                    view.SetOnScreenStateToIntermediateValue(viewModel.OnScreenState());
                }
            }
        }
    }
}
