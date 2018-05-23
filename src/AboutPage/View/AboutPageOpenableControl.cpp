// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageOpenableControl.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageOpenableControl::AboutPageOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
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
