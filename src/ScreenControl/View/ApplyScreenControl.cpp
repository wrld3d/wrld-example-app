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
                if (viewModel.IsOffScreen())
                {
                    view.SetOffScreen();
                }
                else if (viewModel.IsOnScreen())
                {
                    view.SetOnScreen();
                }
            }

            void ApplyMovement(IMovableScreenControlViewModel& movableViewModel, IMovableScreenControlView& movableView)
            {
                movableView.SetOffsetFromDefaultPosition(
                        movableViewModel.GetOffsetFromDefaultPosition());
            }
        }
    }
}
