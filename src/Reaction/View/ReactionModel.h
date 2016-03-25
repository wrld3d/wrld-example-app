// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
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
                IReactionControllerModel& m_reactionControllerModel;

                std::vector<OpenableControl::View::IOpenableControlViewModel*> m_openables;
                std::vector<ScreenControl::View::IScreenControlViewModel*> m_reactors;

                Menu::View::IMenuIgnoredReactionModel& m_menuIgnoredReaction;

                Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

            public:
                ReactionModel(IReactionControllerModel& reactionControllerModel,
                              const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                              const std::vector<ScreenControl::View::IScreenControlViewModel*>& reactors,
                              Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction);

                ~ReactionModel();

            private:

                void UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float openState);

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
