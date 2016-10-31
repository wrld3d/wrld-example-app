// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionRouteGeometryModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            DirectionRouteGeometryModel::DirectionRouteGeometryModel(std::string type, const  std::vector<Eegeo::Space::LatLong>& coordinates)
            : m_type(type)
            , m_coordinates(coordinates)
            {
            
            }
            
            DirectionRouteGeometryModel::~DirectionRouteGeometryModel()
            {
            
            }
            
            const std::string& DirectionRouteGeometryModel::GetType() const
            {
                return m_type;
            }
            
            const std::vector<Eegeo::Space::LatLong>& DirectionRouteGeometryModel::GetCoordinates() const
            {
                return m_coordinates;
            }
        }
    }
}