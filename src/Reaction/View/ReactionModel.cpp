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
                , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ReactionModel, OpenableControl::View::IOpenableControlViewModel&, float>))(this, &ReactionModel::MenuOpenStateChangeHandler))
            {
                for(OpenableControl::View::TOpenables::const_iterator it = m_openables->begin();
                        it != m_openables->end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }
            }

            ReactionModel::~ReactionModel()
            {
                for(OpenableControl::View::TOpenables::const_iterator it = m_openables->begin();
                        it != m_openables->end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }

                Eegeo_DELETE m_pMenuOpenStateChangedCallback;
            }

            void ReactionModel::UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& changingViewModel, float openState)
            {
                for(ScreenControl::View::TReactors::const_iterator it = m_reactors->begin();
                        it != m_reactors->end();
                        ++ it)
                {
                    ScreenControl::View::IScreenControlViewModel& reactor = **it;

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
