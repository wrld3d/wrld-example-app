// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonScreenControl : public ScreenControl::View::ScreenControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                FlattenButtonScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
