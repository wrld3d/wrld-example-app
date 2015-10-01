// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            class SwallowOfficeResultMenuOptionSelectedMessage
            {
            public:
                SwallowOfficeResultMenuOptionSelectedMessage(const Eegeo::Space::LatLong& location,
                                                             float headingDegrees,
                                                             float distance);
                
                const Eegeo::Space::LatLong& GetLocation() const;
                
                float GetHeadingDegrees() const;
                
                float GetDistance() const;
                
            private:
                Eegeo::Space::LatLong m_location;
                float m_headingDegrees;
                float m_distance;
            };
        }
    }
}