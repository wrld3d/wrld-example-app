// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinInFocusChangedLocationMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinInFocusChangedLocationMessage::WorldPinInFocusChangedLocationMessage(const Eegeo::v2& screenLocation)
            : m_screenLocation(screenLocation)
        {

        }

        const Eegeo::v2& WorldPinInFocusChangedLocationMessage::ScreenLocation() const
        {
            return m_screenLocation;
        }
    }
}