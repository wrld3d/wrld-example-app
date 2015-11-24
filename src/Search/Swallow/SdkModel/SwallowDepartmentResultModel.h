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
                class SwallowDepartmentResultModel
                {
                private:
                    std::string m_name;
                    std::string m_imageUrl;
                    std::string m_description;
                    
                public:
                    
                    SwallowDepartmentResultModel(const std::string& name,
                                               const std::string& imageUrl,
                                               const std::string& description);
                    
                    SwallowDepartmentResultModel();
                    
                    ~SwallowDepartmentResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetDescription() const;
                };
            }
        }
    }
}