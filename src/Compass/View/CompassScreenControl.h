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
                                         public ScreenControl::View::IMultiStateScreenControlViewModel,
                                         private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

                ScreenControl::View::TScreenControlViewState m_viewState;

            public:

                enum DisplayMode {Default, Navigation};
                CompassScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const override;

                ScreenControl::View::TScreenControlViewState GetState() override { return m_viewState; }

                void SetState(
                        ScreenControl::View::TScreenControlViewState screenControlViewPosition) override;
            };
        }
    }
}
