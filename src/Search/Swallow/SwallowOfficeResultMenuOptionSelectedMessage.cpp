// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            SwallowOfficeResultMenuOptionSelectedMessage::SwallowOfficeResultMenuOptionSelectedMessage(const Eegeo::Space::LatLong& location,
                                                                                                       float headingDegrees,
                                                                                                       float distance)
            : m_location(location)
            , m_headingDegrees(headingDegrees)
            , m_distance(distance)
            {
                
            }
            
            const Eegeo::Space::LatLong& SwallowOfficeResultMenuOptionSelectedMessage::GetLocation() const
            {
                return m_location;
            }
            
            float SwallowOfficeResultMenuOptionSelectedMessage::GetHeadingDegrees() const
            {
                return m_headingDegrees;
            }
            
            float SwallowOfficeResultMenuOptionSelectedMessage::GetDistance() const
            {
                return m_distance;
            }
        }
    }
}