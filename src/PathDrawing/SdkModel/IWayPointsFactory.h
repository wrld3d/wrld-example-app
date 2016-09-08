// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WayPoint.h"
#include "WayPointType.h"
#include "Space.h"
#include <string>

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class IWayPointsFactory
            {
            public:
                virtual ~IWayPointsFactory() { }
                
                virtual ExampleApp::PathDrawing::WayPoint* CreateWayPoint(const int wpId
                                                                          , const ExampleApp::PathDrawing::WayPointType::Values m_type
                                                                          , Eegeo::Space::LatLong& m_location
                                                                          , const std::string& m_title = "") = 0;
            };
        }
    }
}
