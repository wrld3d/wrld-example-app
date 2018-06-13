// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionModel.h"
#include "MathFunc.h"
#include "IIdentity.h"
#include "IReactionControllerModel.h"
#include "IReaction.h"
#include <algorithm>

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionModel::ReactionModel(const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                                         const std::vector<IReaction*>& reactions,
                                         Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction)
                : m_openables(openables)
                , m_reactions(reactions)
                , m_menuIgnoredReaction(menuIgnoredReaction)
                , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<ReactionModel, OpenableControl::View::IOpenableControlViewModel&>))(this, &ReactionModel::MenuOpenStateChangeHandler))
            {
                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_openables.begin();
                        it != m_openables.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }
            }

            ReactionModel::~ReactionModel()
            {
                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_openables.begin();
                        it != m_openables.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }

                Eegeo_DELETE m_pMenuOpenStateChangedCallback;
            }

            void ReactionModel::UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& changingViewModel)
            {
                for(auto it = m_reactions.begin();
                        it != m_reactions.end();
                        ++ it)
                {
                    IReaction& reaction = **it;

                    if(reaction.ReactionToOpenableIdentity() == changingViewModel.GetIdentity())
                    {
                        reaction.Perform();
                    }
                }
            }

            void ReactionModel::MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel)
            {
                Eegeo::Helpers::TIdentity identity = viewModel.GetIdentity();

                if (m_menuIgnoredReaction.IsIgnored(identity))
                {
                    return;
                }

                UpdateOnScreenStatesInReactionToMenuOpenStateChange(viewModel);
            }
        }
    }
}
