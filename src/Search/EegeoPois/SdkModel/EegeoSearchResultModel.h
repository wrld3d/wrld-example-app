// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchResultModel
                {
                    std::string m_phone;
                    std::string m_webUrl;
                    std::string m_imageUrl;
                    
                public:
                    
                    EegeoSearchResultModel(const std::string& phone,
                                      const std::string& webUrl,
                                      const std::string& imageUrl);
                    
                    EegeoSearchResultModel();
                    
                    ~EegeoSearchResultModel();
                    
                    const std::string& GetPhone() const;

                    const std::string& GetWebUrl() const;
                    
                    bool HasImage() const;
                    
                    const std::string& GetImageUrl() const;
                };
            }
        }
    }
}
