// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointsFactory.h"
#include "WayPoint.h"
namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            ExampleApp::PathDrawing::WayPoint* WayPointsFactory::CreateWayPoint(const int wpId
                                                                                , const ExampleApp::PathDrawing::WayPointType::Values m_type
                                                                                , Eegeo::Space::LatLong& m_location
                                                                                , const std::string& m_title)
            {
                return Eegeo_NEW(ExampleApp::PathDrawing::WayPoint)(wpId, m_type, m_location, m_title);
            }
        }
    }
}
