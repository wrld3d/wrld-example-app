#pragma once

#include "IIdentity.h"
#include "IReaction.h"
#include "IReactionScreenOffsetProvider.h"
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
                IReactionScreenOffsetProvider& m_offsetProvider;
                Eegeo::Helpers::TCallback0<ReactionPushScreenControl> m_offsetUpdateCallback;

                void Update();
            public:
                ReactionPushScreenControl(const OpenableControl::View::IOpenableControlViewModel& openableControl,
                                           ScreenControl::View::IMovableScreenControlViewModel& screenControlToMove,
                                          IReactionScreenOffsetProvider& offsetProvider);
                ~ReactionPushScreenControl();

                Eegeo::Helpers::TIdentity ReactionToOpenableIdentity() override;

                void Perform() override;
            };
        }
    }
}
