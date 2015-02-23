// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationScreenControl : public ScreenControl::View::ScreenControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                MyPinCreationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
