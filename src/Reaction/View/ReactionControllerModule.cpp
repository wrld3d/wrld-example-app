// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionControllerModule.h"
#include "ReactionControllerModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionControllerModule::ReactionControllerModule(const Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction)
            {
                m_pReactionControllerModel = Eegeo_NEW(ReactionControllerModel)(menuIgnoredReaction);
            }

            ReactionControllerModule::~ReactionControllerModule()
            {
                Eegeo_DELETE m_pReactionControllerModel;
            }

            IReactionControllerModel& ReactionControllerModule::GetReactionControllerModel() const
            {
                return *m_pReactionControllerModel;
            }
        }
    }
}
