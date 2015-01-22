// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModeChangedMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassModeChangedMessage::CompassModeChangedMessage(GpsMode::Values mode)
            : m_mode(mode)
        {
        }

        GpsMode::Values CompassModeChangedMessage::GetMode() const
        {
            return m_mode;
        }
    }
}
