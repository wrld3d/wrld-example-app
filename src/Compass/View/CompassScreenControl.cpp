// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassScreenControl.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View {
            CompassScreenControl::CompassScreenControl(bool initiallyOnScreen,
                                                       Eegeo::Helpers::TIdentity identity)
                    : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen),
                      m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity CompassScreenControl::GetIdentity() const
            {
                return m_identity;
            }

            void CompassScreenControl::SetOffsetFromDefaultPosition(
                    ScreenControl::View::IScreenControlViewPosition screenControlViewPosition)
            {
                m_viewPosition = screenControlViewPosition;
                AddToScreen();
            }
        }
    }
}
