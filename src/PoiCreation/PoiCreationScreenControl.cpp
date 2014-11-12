// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationScreenControl.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationScreenControl::PoiCreationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
        : ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity PoiCreationScreenControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
