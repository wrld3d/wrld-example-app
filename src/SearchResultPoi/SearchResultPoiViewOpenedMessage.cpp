// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewOpenedMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiViewOpenedMessage::SearchResultPoiViewOpenedMessage(const std::string& imageUrl,
                                                                           const std::string& ratingsImageUrl)
        : m_imageUrl(imageUrl)
        , m_ratingsImageUrl(ratingsImageUrl)
        {
            
        }
        
        const std::string& SearchResultPoiViewOpenedMessage::GetImageUrl() const
        {
            return m_imageUrl;
        }
        
        const std::string& SearchResultPoiViewOpenedMessage::GetRatingsImageUrl() const
        {
            return m_ratingsImageUrl;
        }
    }
}
