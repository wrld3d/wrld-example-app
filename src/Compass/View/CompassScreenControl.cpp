// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassScreenControl.h"
#include "ICompassViewModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View {
            CompassScreenControl::CompassScreenControl(bool initiallyOnScreen,
                                                       Eegeo::Helpers::TIdentity identity)
                    : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                    , m_identity(identity)
                    , m_viewState(DisplayMode::Default)
            {
            }

            Eegeo::Helpers::TIdentity CompassScreenControl::GetIdentity() const
            {
                return m_identity;
            }

            void CompassScreenControl::SetState(
                    ScreenControl::View::TScreenControlViewState screenControlViewState)
            {
                m_viewState = screenControlViewState;
                AddToScreen();
            }
        }
    }
}
