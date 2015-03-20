// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        class SearchResultPoiViewImageDownloadCompletedMessage
        {
        private:
            std::string m_imageUrl;
            const std::vector<Byte>* m_pImageBytes;
            bool m_success;
            
        public:
            SearchResultPoiViewImageDownloadCompletedMessage(const std::string& imageUrl,
                                                             const std::vector<Byte>* pImageBytes,
                                                             bool success);
            
            const std::string& GetImageUrl() const;
            
            const std::vector<Byte>* GetImageBytes() const;
            
            bool IsSuccess() const;
        };
    }
}
