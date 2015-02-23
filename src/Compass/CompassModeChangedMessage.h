// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CompassGpsMode.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassModeChangedMessage
        {
        private:
            GpsMode::Values m_mode;

        public:
            CompassModeChangedMessage(GpsMode::Values mode);

            GpsMode::Values GetMode() const;
        };
    }
}
