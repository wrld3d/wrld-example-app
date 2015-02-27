// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewImageDownloadCompletedMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiViewImageDownloadCompletedMessage::SearchResultPoiViewImageDownloadCompletedMessage(const std::string& imageUrl,
                                                                                                           const std::vector<Byte>* pImageBytes,
                                                                                                           bool isSuccess)
        : m_imageUrl(imageUrl)
        , m_pImageBytes(pImageBytes)
        , m_success(isSuccess)
        {
            
        }
        
        const std::string& SearchResultPoiViewImageDownloadCompletedMessage::GetImageUrl() const
        {
            return m_imageUrl;
        }
        
        const std::vector<Byte>* SearchResultPoiViewImageDownloadCompletedMessage::GetImageBytes() const
        {
            return m_pImageBytes;
        }
        
        bool SearchResultPoiViewImageDownloadCompletedMessage::IsSuccess() const
        {
            return m_success;
        }
    }
}
