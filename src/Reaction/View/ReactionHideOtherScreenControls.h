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
            class ReactionHideOtherScreenControls : public IReaction
            {
                const OpenableControl::View::IOpenableControlViewModel& m_openableControl;
                const std::vector<ScreenControl::View::IScreenControlViewModel *> m_screenControlsToHide;
            public:
                ReactionHideOtherScreenControls(const OpenableControl::View::IOpenableControlViewModel& openableControl,
                                           const std::vector<ScreenControl::View::IScreenControlViewModel *>& screenControlsToHide);

                ReactionHideOtherScreenControls(const OpenableControl::View::IOpenableControlViewModel& openableControl,
                                           ScreenControl::View::IScreenControlViewModel& screenControlToHide);
                ~ReactionHideOtherScreenControls() { }

                Eegeo::Helpers::TIdentity ReactionToOpenableIdentity() override;

                void Perform() override;
            };
        }
    }
}
