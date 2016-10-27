// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            DirectionRouteModel::DirectionRouteModel(std::string code,std::string type,const std::vector<ExampleApp::PathDrawing::WayPointModel>& wayPoints,const std::vector<DirectionInnerRouteModel>& innerRoutes)
            : m_code(code)
            , m_type(type)
            , m_wayPoints(wayPoints)
            , m_innerRoutes(innerRoutes)
            {
            
            }
            
            DirectionRouteModel::~DirectionRouteModel()
            {
            
            }
            
            const std::string& DirectionRouteModel::GetCode() const
            {
                return m_code;
            }
            
            const std::string& DirectionRouteModel::GetType() const
            {
                return m_type;
            }
            
            const std::vector<DirectionInnerRouteModel>& DirectionRouteModel::GetInnerRoutes() const
            {
                return m_innerRoutes;
            }
            
            const std::vector<ExampleApp::PathDrawing::WayPointModel>& DirectionRouteModel::GetWayPoints() const
            {
                return m_wayPoints;
            }

            
        }
    }
}