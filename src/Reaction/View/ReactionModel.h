// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
#include "IReactionModel.h"
#include "IMenuViewModel.h"
#include "ICallback.h"
#include "IMenuIgnoredReactionModel.h"
#include "IOpenableControlViewModel.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionModel : public IReactionModel, private Eegeo::NonCopyable
            {
                const std::shared_ptr<IReactionControllerModel> m_reactionControllerModel;

                const std::shared_ptr<OpenableControl::View::TOpenables> m_openables;
                const std::shared_ptr<ScreenControl::View::TReactors> m_reactors;

                const std::shared_ptr<Menu::View::IMenuIgnoredReactionModel> m_menuIgnoredReaction;

                Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

            public:
                ReactionModel(const std::shared_ptr<IReactionControllerModel>& reactionControllerModel,
                              const std::shared_ptr<OpenableControl::View::TOpenables>& openables,
                              const std::shared_ptr<ScreenControl::View::TReactors>& reactors,
                              const std::shared_ptr<Menu::View::IReactorIgnoredReactionModel>& menuIgnoredReaction);

                ~ReactionModel();

            private:

                void UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float openState);

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
