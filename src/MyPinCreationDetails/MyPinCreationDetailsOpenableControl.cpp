// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        MyPinCreationDetailsOpenableControl::MyPinCreationDetailsOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity MyPinCreationDetailsOpenableControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
