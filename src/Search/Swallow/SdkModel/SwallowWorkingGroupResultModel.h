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
                class SwallowWorkingGroupResultModel
                {
                private:
                    std::string m_name;
                    std::string m_imageUrl;
                    std::string m_description;
                    std::string m_officeLocation;
                    std::vector<std::string> m_desks;
                    
                public:
                    
                    SwallowWorkingGroupResultModel(const std::string& name,
                                                   const std::string& imageUrl,
                                                   const std::string& description,
                                                   const std::string& officeLocation,
                                                   const std::vector<std::string>& desks);
                    
                    SwallowWorkingGroupResultModel();
                    
                    ~SwallowWorkingGroupResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetDescription() const;
                    
                    const std::string& GetOfficeLocation() const;

                    const std::vector<std::string>& GetAllDesks() const;
                };
            }
        }
    }
}