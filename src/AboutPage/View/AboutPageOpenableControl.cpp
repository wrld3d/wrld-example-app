// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageOpenableControl.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageOpenableControl::AboutPageOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::View::IReactionControllerModel& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity AboutPageOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
