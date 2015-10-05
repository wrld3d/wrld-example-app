// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Example
        {
            namespace SdkModel
            {
                class ExampleSearchResultModel
                {
                    std::string m_imageUrl;
                    
                public:
                    
                    ExampleSearchResultModel(const std::string& imageUrl);
                    
                    ExampleSearchResultModel();
                    
                    ~ExampleSearchResultModel();
                    const std::string& GetImageUrl() const;
                };
                
                
            }
        }
    }
}
