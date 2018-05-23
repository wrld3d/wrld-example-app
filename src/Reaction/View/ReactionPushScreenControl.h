#pragma once

#include "IIdentity.h"
#include "IReaction.h"
#include "IScreenControlViewModel.h"
#include "IOpenableControlViewModel.h"
#include <vector>

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionPushScreenControl : public IReaction
            {
                const OpenableControl::View::IOpenableControlViewModel& m_openableControl;
                ScreenControl::View::IMovableScreenControlViewModel& m_screenControlToMove;
                const ScreenControl::View::IScreenControlViewPosition m_destination;
            public:
                ReactionPushScreenControl(const OpenableControl::View::IOpenableControlViewModel& openableControl,
                                           ScreenControl::View::IMovableScreenControlViewModel& screenControlToMove,
                                          const ScreenControl::View::IScreenControlViewPosition destination);
                ~ReactionPushScreenControl() { }

                Eegeo::Helpers::TIdentity ReactionToOpenableIdentity() override;

                void Perform() override;
            };
        }
    }
}
