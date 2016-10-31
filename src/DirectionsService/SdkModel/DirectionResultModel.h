// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "DirectionRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class DirectionResultModel
            {
            private:
                
                std::string m_code;
                std::string m_type;
                std::vector<DirectionRouteModel> m_routes;
                
            public:
                
                DirectionResultModel(std::string code,std::string type,const std::vector<DirectionRouteModel>& routes);
                ~DirectionResultModel();
                
                const std::string& GetCode() const;
                const std::string& GetType() const;
                const std::vector<DirectionRouteModel>& GetRoutes() const;



                
            };
        }
    }
}