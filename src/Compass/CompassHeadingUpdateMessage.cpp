// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassHeadingUpdateMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassHeadingUpdateMessage::CompassHeadingUpdateMessage(float headingRadians)
            : m_headingRadians(headingRadians)
        {
        }

        float CompassHeadingUpdateMessage::GetHeadingRadians() const
        {
            return m_headingRadians;
        }
    }
}
