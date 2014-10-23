// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageOpenableControl.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageOpenableControl::AboutPageOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity AboutPageOpenableControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
