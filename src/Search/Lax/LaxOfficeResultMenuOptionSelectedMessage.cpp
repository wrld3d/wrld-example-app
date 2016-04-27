// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            LaxOfficeResultMenuOptionSelectedMessage::LaxOfficeResultMenuOptionSelectedMessage(const Eegeo::Space::LatLong& location,
                                                                                                       float headingDegrees,
                                                                                                       float distance)
            : m_location(location)
            , m_headingDegrees(headingDegrees)
            , m_distance(distance)
            {
                
            }
            
            const Eegeo::Space::LatLong& LaxOfficeResultMenuOptionSelectedMessage::GetLocation() const
            {
                return m_location;
            }
            
            float LaxOfficeResultMenuOptionSelectedMessage::GetHeadingDegrees() const
            {
                return m_headingDegrees;
            }
            
            float LaxOfficeResultMenuOptionSelectedMessage::GetDistance() const
            {
                return m_distance;
            }
        }
    }
}