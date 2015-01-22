// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinInFocusChangedLocationMessage
        {
            Eegeo::v2 m_screenLocation;

        public:
            WorldPinInFocusChangedLocationMessage(const Eegeo::v2& screenLocation);

            const Eegeo::v2& ScreenLocation() const;
        };
    }
}
