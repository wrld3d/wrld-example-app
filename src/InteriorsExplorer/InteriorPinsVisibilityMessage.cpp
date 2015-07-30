// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinsVisibilityMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        InteriorPinsVisibilityMessage::InteriorPinsVisibilityMessage(bool shouldShowPins)
        : m_shouldShowPins(shouldShowPins)
        {

        }

        bool InteriorPinsVisibilityMessage::GetShouldShowPins() const
        {
            return m_shouldShowPins;
        }
    }
}