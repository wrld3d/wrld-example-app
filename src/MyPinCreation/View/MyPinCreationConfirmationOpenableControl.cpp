// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationConfirmationOpenableControl.h"

namespace ExampleApp
{
    MyPinCreationConfirmationOpenableControl::MyPinCreationConfirmationOpenableControl(Eegeo::Helpers::TIdentity identity,
                Reaction::IReactionControllerModel& reactionControllerModel)
                : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
    {
    }

    Eegeo::Helpers::TIdentity MyPinCreationConfirmationOpenableControl::GetIdentity() const
    {
        return m_identity;
    }
}
