// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationButtonScreenControl.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationButtonScreenControl::PoiCreationButtonScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
        : ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity PoiCreationButtonScreenControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
