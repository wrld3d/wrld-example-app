// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageOpenableControl.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageOpenableControl::AboutPageOpenableControl(const std::shared_ptr<Eegeo::Helpers::IIdentityProvider>& identity, const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity->GetNextIdentity())
            {
            }

            Eegeo::Helpers::TIdentity AboutPageOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
