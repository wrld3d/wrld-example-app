// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPoint.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        WayPoint::WayPoint(const int wpId
                           , const ExampleApp::PathDrawing::WayPointType::Values type
                           , Eegeo::Space::LatLong& location
                           , const std::string& title)
        : m_wpId(wpId)
        , m_type(type)
        , m_location(location)
        , m_title(title)
        {
        }
        
        const int WayPoint::GetWpId()
        {
            return m_wpId;
        }

        const std::string WayPoint::GetTitle()
        {
            return m_title;
        }
        
        const ExampleApp::PathDrawing::WayPointType::Values WayPoint::GetType()
        {
            return m_type;
        }
        
        const Eegeo::Space::LatLong& WayPoint::GetLocation()
        {
            return m_location;
        }
    }

}