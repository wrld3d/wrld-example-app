// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuInitiationScreenControl.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            DirectionsMenuInitiationScreenControl::DirectionsMenuInitiationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity DirectionsMenuInitiationScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
