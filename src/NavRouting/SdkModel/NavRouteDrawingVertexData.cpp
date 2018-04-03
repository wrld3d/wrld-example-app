// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingVertexData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRouteDrawingVertexData::NavRouteDrawingVertexData(double latitudeDegrees, double longitudeDegrees, const std::string& indoorMapId, int indoorMapFloorId,             bool multiFloor)
            : m_latitudeDegrees(latitudeDegrees)
            , m_longitudeDegrees(longitudeDegrees)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            , m_multiFloor(multiFloor)
            {
            }
            
            bool NavRouteDrawingVertexData::operator != (const NavRouteDrawingVertexData& rhs) const
            {
                return m_latitudeDegrees != rhs.m_latitudeDegrees ||
                m_longitudeDegrees != rhs.m_longitudeDegrees ||
                m_indoorMapId != rhs.m_indoorMapId ||
                m_indoorMapFloorId != rhs.m_indoorMapFloorId ||
                m_multiFloor != rhs.m_multiFloor;
            }
            
            bool NavRouteDrawingVertexData::operator == (const NavRouteDrawingVertexData& rhs) const
            {
                return !(*this != rhs);
            }
            
            double NavRouteDrawingVertexData::GetLatitudeDegrees() const
            {
                return m_latitudeDegrees;
            }
            
            double NavRouteDrawingVertexData::GetLongitudeDegrees() const
            {
                return m_longitudeDegrees;
            }
            
            const std::string& NavRouteDrawingVertexData::GetIndoorMapId() const
            {
                return m_indoorMapId;
            }
            
            int NavRouteDrawingVertexData::GetIndoorMapFloorId() const
            {
                return m_indoorMapFloorId;
            }
            bool NavRouteDrawingVertexData::IsMultiFloor() const
            {
                return m_multiFloor;
            }
        }
    }
}
