// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionInnerRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            DirectionInnerRouteModel::DirectionInnerRouteModel(int duration,int distance ,const DirectionRouteGeometryModel& pGeometry)
            : m_duration(duration)
            , m_distance(distance)
            , m_Geometry(pGeometry)
            {
            
            }
            
            DirectionInnerRouteModel::~DirectionInnerRouteModel()
            {
            
            }
            
            const int DirectionInnerRouteModel::GetDuration() const
            {
                return m_duration;
            }
            
            const float DirectionInnerRouteModel::GetDistance() const
            {
                return m_distance;
            }
            
            const DirectionRouteGeometryModel& DirectionInnerRouteModel::GetInnerRouteGeometry() const
            {
                return m_Geometry;
            }
        }
    }
}