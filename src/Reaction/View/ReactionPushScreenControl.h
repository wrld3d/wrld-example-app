#pragma once

#include "IIdentity.h"
#include "IReaction.h"
#include "IReactionScreenStateProvider.h"
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
                ScreenControl::View::IMultiStateScreenControlViewModel& m_screenControlToMove;
                IReactionScreenStateProvider& m_offsetProvider;
                Eegeo::Helpers::TCallback0<ReactionPushScreenControl> m_offsetUpdateCallback;
            public:
                ReactionPushScreenControl(const OpenableControl::View::IOpenableControlViewModel& openableControl,
                                           ScreenControl::View::IMultiStateScreenControlViewModel& screenControlToMove,
                                          IReactionScreenStateProvider& offsetProvider);
                ~ReactionPushScreenControl();

                Eegeo::Helpers::TIdentity ReactionToOpenableIdentity() override;

                void Perform() override;
            };
        }
    }
}
