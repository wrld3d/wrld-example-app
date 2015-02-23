// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OpenableControlViewModelBase.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsOpenableControl : public OpenableControl::View::OpenableControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                MyPinDetailsOpenableControl(Eegeo::Helpers::TIdentity identity,
                                            Reaction::View::IReactionControllerModel& reactionControllerModel);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
