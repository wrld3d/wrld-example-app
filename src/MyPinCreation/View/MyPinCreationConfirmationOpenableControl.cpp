// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationOpenableControl::MyPinCreationConfirmationOpenableControl(Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MyPinCreationConfirmationOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
