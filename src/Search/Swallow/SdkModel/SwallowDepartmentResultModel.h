// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

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
                    std::vector<std::string> m_desks;
                    
                public:
                    
                    SwallowDepartmentResultModel(const std::string& name,
                                                 const std::string& imageUrl,
                                                 const std::string& description,
                                                 const std::vector<std::string>& desks);
                    
                    SwallowDepartmentResultModel();
                    
                    ~SwallowDepartmentResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetDescription() const;
                    
                    const size_t GetNumberOfDesks() const;
                    
                    const std::string& GetDeskAt(int idx) const;
                    
                    const std::vector<std::string>& GetAllDesks() const;
                };
            }
        }
    }
}