// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionResultModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            DirectionResultModel::DirectionResultModel(std::string code,std::string type,const std::vector<DirectionRouteModel>& routes)
            : m_code(code)
            , m_type(type)
            , m_routes(routes)
            {
    
            }

            DirectionResultModel::~DirectionResultModel()
            {
            
            }
            
            const std::string& DirectionResultModel::GetCode() const
            {
                return m_code;
            }
            
            const std::string& DirectionResultModel::GetType() const
            {
                return m_type;
            }
            
            const std::vector<DirectionRouteModel>& DirectionResultModel::GetRoutes() const
            {
                return m_routes;
            }
        }
    }
}