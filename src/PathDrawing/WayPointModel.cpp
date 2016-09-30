// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointModel.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        WayPointModel::WayPointModel(const int wpId
                           , const ExampleApp::PathDrawing::WayPointType::Values type
                           , Eegeo::Space::LatLong& location
                           , const std::string title)
        : m_id(wpId)
        , m_type(type)
        , m_location(location)
        , m_title(title)
        {
        }
        
        const int WayPointModel::GetWpId()
        {
            return m_id;
        }

        const std::string WayPointModel::GetTitle()
        {
            return m_title;
        }
        
        const ExampleApp::PathDrawing::WayPointType::Values WayPointModel::GetType()
        {
            return m_type;
        }
        
        const Eegeo::Space::LatLong& WayPointModel::GetLocation()
        {
            return m_location;
        }
    }

}