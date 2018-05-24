#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionScreenOffsetProvider
            {
            public:
                virtual ScreenControl::View::IScreenControlViewPosition GetOffset() const = 0;
                virtual void InsertOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                virtual void RemoveOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            };
        }
    }
}
