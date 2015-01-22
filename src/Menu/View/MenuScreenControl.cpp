// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuScreenControl.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuScreenControl::MenuScreenControl(Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(false)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MenuScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
