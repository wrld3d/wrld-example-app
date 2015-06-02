// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ScreenControlViewModelBase.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            class InteriorsViewModel : public ScreenControl::View::ScreenControlViewModelBase
            {
            public:
                InteriorsViewModel(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);
                
                Eegeo::Helpers::TIdentity GetIdentity() const;
                
            private:
                Eegeo::Helpers::TIdentity m_identity;
            };
        }
    }
}