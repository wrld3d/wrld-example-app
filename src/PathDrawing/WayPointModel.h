// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WayPointType.h"
#include "space.h"
#include <string>
#include "LatLongAltitude.h"
namespace ExampleApp
{
    namespace PathDrawing
    {
        class WayPointModel : protected Eegeo::NonCopyable
        {
        private:
            const int m_id;
            const std::string m_title;
            const ExampleApp::PathDrawing::WayPointType::Values m_type;
            const Eegeo::Space::LatLong& m_location;
       
        public:
            WayPointModel(const int wpId
                     , const ExampleApp::PathDrawing::WayPointType::Values type
                     , Eegeo::Space::LatLong& location
                     , const std::string title);
            
            const int GetWpId();
            const std::string GetTitle();
            const ExampleApp::PathDrawing::WayPointType::Values GetType();
            const Eegeo::Space::LatLong& GetLocation();
            
            virtual ~WayPointModel() { }
        };
        
    }
}
