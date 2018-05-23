// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IReaction.h"
#include "ReactionModelModule.h"
#include "ReactionModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionModelModule::ReactionModelModule(
                    const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                    const std::vector<IReaction*>& reactors,
                    Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction)
            {
                m_pModel = Eegeo_NEW(ReactionModel)(openables, reactors, menuIgnoredReaction);
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
