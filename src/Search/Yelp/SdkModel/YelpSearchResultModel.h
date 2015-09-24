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
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchResultModel
                {
                    std::string m_phone;
                    std::string m_webUrl;
                    std::string m_vicinity;
                    std::string m_imageUrl;
                    std::string m_ratingImageUrl;
                    std::vector<std::string> m_reviews;
                    int m_reviewCount;
                    
                public:
                    
                    YelpSearchResultModel(const std::string& phone,
                                      const std::string& webUrl,
                                      const std::string& vicinity,
                                      const std::string& imageUrl,
                                      const std::string& ratingImageUrl,
                                      const std::vector<std::string>& reviews,
                                      int reviewCount);
                    
                    YelpSearchResultModel();
                    
                    ~YelpSearchResultModel();
                    
                    const std::string& GetPhone() const;

                    const std::string& GetWebUrl() const;

                    const std::string& GetVicinity() const;
                    
                    bool HasImage() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    bool HasRatingImage() const;
                    
                    const std::string& GetRatingImageUrl() const;
                    
                    const std::vector<std::string>& GetReviews() const;
                    
                    const int GetReviewCount() const;
                    
                };
            }
        }
    }
}
