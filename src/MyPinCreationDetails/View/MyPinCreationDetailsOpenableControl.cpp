// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsOpenableControl::MyPinCreationDetailsOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::View::IReactionControllerModel& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MyPinCreationDetailsOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
