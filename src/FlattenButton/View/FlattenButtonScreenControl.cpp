// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonScreenControl.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonScreenControl::FlattenButtonScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity FlattenButtonScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
