// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "DirectionRouteGeometryModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class DirectionInnerRouteModel
            {
            public:
                
                DirectionInnerRouteModel(int duration,int distance  , const DirectionRouteGeometryModel& pGeometry);
                ~DirectionInnerRouteModel();
                const int GetDuration() const;
                const float GetDistance() const;
                const DirectionRouteGeometryModel& GetInnerRouteGeometry() const;
                
            private:
                
                //"legs":[],
                int m_duration;
                float m_distance;
                const DirectionRouteGeometryModel m_Geometry;
            };
        
        }
    }
}