// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuScreenControl : public ScreenControl::View::ScreenControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                MenuScreenControl(Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
