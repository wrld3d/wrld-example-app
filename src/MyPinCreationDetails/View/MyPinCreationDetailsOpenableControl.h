// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OpenableControlViewModelBase.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsOpenableControl : public OpenableControl::View::OpenableControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                MyPinCreationDetailsOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::View::IReactionControllerModel& reactionControllerModel);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
