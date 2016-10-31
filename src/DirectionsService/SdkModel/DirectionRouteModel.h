// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "WayPointModel.h"
#include "DirectionInnerRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            class DirectionRouteModel
            {
                
            private:
                
                std::string m_code;
                std::string m_type;
                std::vector<ExampleApp::PathDrawing::WayPointModel> m_wayPoints;
                std::vector<DirectionInnerRouteModel> m_innerRoutes;
            
            public:
            
                DirectionRouteModel(std::string code,std::string type,const std::vector<ExampleApp::PathDrawing::WayPointModel>& wayPoints,const std::vector<DirectionInnerRouteModel>& innerRoutes);
                ~DirectionRouteModel();
                
                const std::string& GetCode() const;
                const std::string& GetType() const;
                const std::vector<DirectionInnerRouteModel>& GetInnerRoutes() const;
                const std::vector<ExampleApp::PathDrawing::WayPointModel>& GetWayPoints() const;


            };
        
        }
    }
}

