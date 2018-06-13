// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuOpenableControl.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuOpenableControl::MenuOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MenuOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
