// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionModel.h"
#include "MathFunc.h"
#include "IIdentity.h"
#include "IReactionControllerModel.h"
#include "ReactorIgnoredReactionModel.h"
#include <algorithm>

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionModel::ReactionModel(const std::shared_ptr<IReactionControllerModel>& reactionControllerModel,
                                         const std::shared_ptr<OpenableControl::View::TOpenables>& openables,
                                         const std::shared_ptr<ScreenControl::View::TReactors>& reactors,
                                         const std::shared_ptr<Menu::View::IReactorIgnoredReactionModel>& menuIgnoredReaction)
                : m_reactionControllerModel(reactionControllerModel)
                , m_openables(openables)
                , m_reactors(reactors)
                , m_menuIgnoredReaction(menuIgnoredReaction)
                , m_menuOpenStateChangedCallback(this, &ReactionModel::MenuOpenStateChangeHandler)
                , m_openableAdded(this, &ReactionModel::OnOpenableAdded)
                , m_openableRemoved(this, &ReactionModel::OnOpenableRemoved)
            {
                m_openables->InsertItemAddedCallback(m_openableAdded);
                m_openables->InsertItemRemovedCallback(m_openableRemoved);
            }

            ReactionModel::~ReactionModel()
            {
                m_openables->RemoveItemRemovedCallback(m_openableRemoved);
                m_openables->RemoveItemAddedCallback(m_openableAdded);
            }
            
            void ReactionModel::OnOpenableAdded(OpenableControl::View::IOpenableControlViewModel*& openable)
            {
                openable->InsertOpenStateChangedCallback(m_menuOpenStateChangedCallback);
            }
            
            void ReactionModel::OnOpenableRemoved(OpenableControl::View::IOpenableControlViewModel*& openable)
            {
                openable->RemoveOpenStateChangedCallback(m_menuOpenStateChangedCallback);
            }

            void ReactionModel::UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& changingViewModel, float openState)
            {
                for(size_t i = 0; i<m_reactors->GetItemCount(); ++i)
                {
                    ScreenControl::View::IScreenControlViewModel& reactor = *m_reactors->GetItemAtIndex(i);

                    if(reactor != changingViewModel)
                    {
                        reactor.UpdateOnScreenState(1.f - openState);
                    }
                }
            }

            void ReactionModel::MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                Eegeo::Helpers::TIdentity identity = viewModel.GetIdentity();

                if (m_menuIgnoredReaction->IsIgnored(identity))
                {
                    return;
                }
                
                if(m_reactionControllerModel->HasModalControl(viewModel.GetIdentity()))
                {
                    UpdateOnScreenStatesInReactionToMenuOpenStateChange(viewModel, openState);
                }
            }
        }
    }
}
