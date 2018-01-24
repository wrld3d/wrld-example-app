#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionScreenStateProvider
            {
            public:
                virtual ScreenControl::View::TScreenControlViewState GetState() const = 0;
                virtual void InsertStateUpdatedCallback(Eegeo::Helpers::ICallback0 &closedCallback) = 0;
                virtual void RemoveStateUpdatedCallback(Eegeo::Helpers::ICallback0 &closedCallback) = 0;
            };
        }
    }
}
