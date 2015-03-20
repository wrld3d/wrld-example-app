// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkScreenControl.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkScreenControl::WatermarkScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity WatermarkScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
