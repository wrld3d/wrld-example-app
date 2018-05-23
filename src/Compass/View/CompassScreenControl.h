// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassScreenControl : public ScreenControl::View::ScreenControlViewModelBase,
                                         public ScreenControl::View::IMovableScreenControlViewModel,
                                         private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

                ScreenControl::View::IScreenControlViewPosition m_viewPosition;

            public:
                CompassScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const override;

                ScreenControl::View::IScreenControlViewPosition GetOffsetFromDefaultPosition() override { return m_viewPosition; }

                void SetOffsetFromDefaultPosition(
                        ScreenControl::View::IScreenControlViewPosition screenControlViewPosition) override;
            };
        }
    }
}
