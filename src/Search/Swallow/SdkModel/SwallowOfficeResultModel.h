// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowOfficeResultModel
                {
                private:
                    std::string m_name;
                    float m_distance;
                    float m_headingDegrees;
                    
                public:
                    
                    SwallowOfficeResultModel(const std::string& name,
                                             float distance,
                                             float headingDegrees);
                    
                    SwallowOfficeResultModel();
                    
                    ~SwallowOfficeResultModel();
                    
                    const std::string& GetName() const;
                    
                    float GetDistance() const;
                    
                    float GetHeadingDegrees() const;
                };
            }
        }
    }
}