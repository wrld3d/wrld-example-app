// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionModelModule.h"
#include "ReactionModel.h"
#include "ReactionControllerModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionModelModule::ReactionModelModule(IReactionControllerModel& reactionControllerModel,
                    const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                    const std::vector<ScreenControl::View::IScreenControlViewModel*>& reactors,
                    Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction)
            {
                m_pModel = Eegeo_NEW(ReactionModel)(reactionControllerModel, openables, reactors, menuIgnoredReaction);
            }

            ReactionModelModule::~ReactionModelModule()
            {
                Eegeo_DELETE m_pModel;
            }

            IReactionModel& ReactionModelModule::GetReactionModel() const
            {
                return *m_pModel;
            }
        }
    }
}
