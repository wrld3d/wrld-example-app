// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Reaction.h"
#include "IReactionControllerModule.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionControllerModule: public IReactionControllerModule, private Eegeo::NonCopyable
            {
            private:
                IReactionControllerModel* m_pReactionControllerModel;

            public:
                ReactionControllerModule(const Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction);

                ~ReactionControllerModule();

                IReactionControllerModel& GetReactionControllerModel() const;
            };
        }
    }
}
