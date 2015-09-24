// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpSearchResultModel::YelpSearchResultModel()
                : m_phone("")
                , m_webUrl("")
                , m_vicinity("")
                , m_imageUrl("")
                , m_ratingImageUrl("")
                , m_reviews()
                , m_reviewCount(0)
                {
                    
                }
                
                YelpSearchResultModel::YelpSearchResultModel(const std::string& phone,
                                                     const std::string& webUrl,
                                                     const std::string& vicinity,
                                                     const std::string& imageUrl,
                                                     const std::string& ratingImageUrl,
                                                     const std::vector<std::string>& reviews,
                                                     const int reviewCount)
                    : m_phone(phone)
                    , m_webUrl(webUrl)
                    , m_vicinity(vicinity)
                    , m_imageUrl(imageUrl)
                    , m_ratingImageUrl(ratingImageUrl)
                    , m_reviews(reviews)
                    , m_reviewCount(reviewCount)
                {
                }

                YelpSearchResultModel::~YelpSearchResultModel()
                {

                }

                const std::string& YelpSearchResultModel::GetPhone() const
                {
                    return m_phone;
                }

                const std::string& YelpSearchResultModel::GetWebUrl() const
                {
                    return m_webUrl;
                }

                const std::string& YelpSearchResultModel::GetVicinity() const
                {
                    return m_vicinity;
                }
                
                bool YelpSearchResultModel::HasImage() const
                {
                    return !m_imageUrl.empty();
                }
                
                const std::string& YelpSearchResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                bool YelpSearchResultModel::HasRatingImage() const
                {
                    return !m_ratingImageUrl.empty();
                }
                
                const std::string& YelpSearchResultModel::GetRatingImageUrl() const
                {
                    return m_ratingImageUrl;
                }
                
                const std::vector<std::string>& YelpSearchResultModel::GetReviews() const
                {
                    return m_reviews;
                }
                
                const int YelpSearchResultModel::GetReviewCount() const
                {
                    return m_reviewCount;
                }
            }
        }
    }
}
