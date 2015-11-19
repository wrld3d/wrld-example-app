// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkData
            {
            public:
                WatermarkData()
                : m_shouldShowShadow(false)
                {
                    
                }
                
                WatermarkData(const std::string& imageAssetName,
                              const std::string& popupTitle,
                              const std::string& popupBody,
                              const std::string& webUrl,
                              bool shouldShowShadow)
                : m_imageAssetName(imageAssetName)
                , m_popupTitle(popupTitle)
                , m_popupBody(popupBody)
                , m_webUrl(webUrl)
                , m_shouldShowShadow(shouldShowShadow)
                {
                    
                }
                
                std::string ImageAssetName() const { return m_imageAssetName; }
                std::string PopupTitle() const { return m_popupTitle; }
                std::string PopupBody() const { return m_popupBody; }
                std::string WebUrl() const { return m_webUrl; }
                bool ShouldShowShadow() const { return m_shouldShowShadow; }
                
            private:
                std::string m_imageAssetName;
                std::string m_popupTitle;
                std::string m_popupBody;
                std::string m_webUrl;
                bool m_shouldShowShadow;
            };
        }
    }
}