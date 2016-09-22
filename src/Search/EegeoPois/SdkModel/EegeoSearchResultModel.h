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
                    std::string m_address;
                    std::string m_description;
                    
                public:
                    
                    EegeoSearchResultModel(const std::string& phone,
                                           const std::string& webUrl,
                                           const std::string& address,
                                           const std::string& description,
                                           const std::string& imageUrl);
                    
                    EegeoSearchResultModel();
                    
                    ~EegeoSearchResultModel();
                    
                    const std::string& GetPhone() const;

                    const std::string& GetWebUrl() const;
                    
                    const std::string& GetAddress() const;
                    
                    const std::string& GetDescription() const;
                    
                    bool HasImage() const;
                    
                    const std::string& GetImageUrl() const;
                };
            }
        }
    }
}
