// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
#include "ReactionModel.h"
#include "OpenableControlViewModelIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "IReactionModelModule.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionModelModule: public IReactionModelModule, private Eegeo::NonCopyable
            {
            private:
                IReactionModel* m_pModel;
            public:
                ReactionModelModule(IReactionControllerModel& reactionControllerModel,
                                    const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                                    const std::vector<ScreenControl::View::IScreenControlViewModel*>& reactors,
                                    Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction);

                ~ReactionModelModule();

                IReactionModel& GetReactionModel() const;
            };
        }
    }
}
