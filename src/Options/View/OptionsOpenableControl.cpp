// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsOpenableControl.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsOpenableControl::OptionsOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity OptionsOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
