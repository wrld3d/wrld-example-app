// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowOfficeResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowOfficeResultModel::SwallowOfficeResultModel(const std::string& name,
                                                                   float distance,
                                                                   float headingDegrees)
                : m_name(name)
                , m_distance(distance)
                , m_headingDegrees(headingDegrees)
                {
                    
                }
                
                SwallowOfficeResultModel::SwallowOfficeResultModel()
                {
                    
                }
                
                SwallowOfficeResultModel::~SwallowOfficeResultModel()
                {
                    
                }
                
                const std::string& SwallowOfficeResultModel::GetName() const
                {
                    return m_name;
                }
                
                float SwallowOfficeResultModel::GetDistance() const
                {
                    return m_distance;
                }
                
                float SwallowOfficeResultModel::GetHeadingDegrees() const
                {
                    return m_headingDegrees;
                }
            }
        }
    }
}