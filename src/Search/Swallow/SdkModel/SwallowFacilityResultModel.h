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
                class SwallowFacilityResultModel
                {
                private:
                    std::string m_name;
                    std::string m_imageUrl;
                    std::string m_description;
                    std::string m_officeLocation;
                    
                public:
                    
                    SwallowFacilityResultModel(const std::string& name,
                                               const std::string& imageUrl,
                                               const std::string& description,
                                               const std::string& officeLocation);
                    
                    SwallowFacilityResultModel();
                    
                    ~SwallowFacilityResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetDescription() const;
                    
                    const std::string& GetOfficeLocation() const;
                };
            }
        }
    }
}