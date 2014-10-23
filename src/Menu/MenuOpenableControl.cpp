// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MenuOpenableControl.h"

namespace ExampleApp
{
    namespace Menu
    {
        MenuOpenableControl::MenuOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity MenuOpenableControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
