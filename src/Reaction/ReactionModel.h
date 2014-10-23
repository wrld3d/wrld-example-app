// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
#include "IReactionModel.h"
#include "IMenuViewModel.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Reaction
    {
        class ReactionModel : public IReactionModel, private Eegeo::NonCopyable
        {
            IReactionControllerModel& m_reactionControllerModel;
            
            std::vector<OpenableControlViewModel::IOpenableControlViewModel*> m_openables;
            std::vector<ScreenControlViewModel::IScreenControlViewModel*> m_reactors;
            
            Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;
            
        public:
            ReactionModel(IReactionControllerModel& reactionControllerModel,
                          const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& openables,
                          const std::vector<ScreenControlViewModel::IScreenControlViewModel*>& reactors);
            
            ~ReactionModel();
            
        private:
            
            void UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float openState);
            
            void MenuOpenStateChangeHandler(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);
        };
    }
}
