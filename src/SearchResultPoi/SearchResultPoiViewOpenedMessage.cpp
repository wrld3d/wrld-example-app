// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewOpenedMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiViewOpenedMessage::SearchResultPoiViewOpenedMessage(const std::string& imageUrl)
        : m_imageUrl(imageUrl)
        {
            
        }
        
        const std::string& SearchResultPoiViewOpenedMessage::GetImageUrl() const
        {
            return m_imageUrl;
        }
    }
}
