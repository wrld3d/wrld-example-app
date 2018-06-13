// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
#include "IReaction.h"
#include "IReactionModel.h"
#include "IMenuViewModel.h"
#include "ICallback.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionModel : public IReactionModel, private Eegeo::NonCopyable
            {
                std::vector<OpenableControl::View::IOpenableControlViewModel*> m_openables;
                std::vector<IReaction*> m_reactions;

                Menu::View::IMenuIgnoredReactionModel& m_menuIgnoredReaction;

                Eegeo::Helpers::ICallback1<OpenableControl::View::IOpenableControlViewModel&>* m_pMenuOpenStateChangedCallback;

            public:
                ReactionModel(const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                              const std::vector<IReaction*>& reactions,
                              Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction);

                ~ReactionModel();

            private:

                void UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel);

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel);
            };
        }
    }
}
