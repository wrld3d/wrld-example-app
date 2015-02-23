// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinInFocusScreenControl.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinInFocusScreenControl::WorldPinInFocusScreenControl(Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(false)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity WorldPinInFocusScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
