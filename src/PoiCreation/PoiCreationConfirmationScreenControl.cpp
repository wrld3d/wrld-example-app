// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationConfirmationScreenControl.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationConfirmationScreenControl::PoiCreationConfirmationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
        : ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity PoiCreationConfirmationScreenControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
