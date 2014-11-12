// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationScreenControl : public ScreenControlViewModel::ScreenControlViewModelBase, private Eegeo::NonCopyable
        {
            Eegeo::Helpers::TIdentity m_identity;
            
        public:
            PoiCreationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);
            
            Eegeo::Helpers::TIdentity GetIdentity() const;
        };
    }
}
