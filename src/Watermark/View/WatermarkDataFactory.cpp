// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkDataFactory.h"


namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkDataFactory::WatermarkDataFactory(const std::string& appName,
                                                       const std::string& googleAnalyticsReferrerToken)
            : m_appName(appName)
            , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
            {
                
            }
            
            WatermarkData WatermarkDataFactory::Create(const std::string& imageAssetUrl,
                                                       const std::string& popupTitle,
                                                       const std::string& popupBody,
                                                       const std::string& webUrl,
                                                       const bool shouldShowShadow)
            {
                return WatermarkData(imageAssetUrl,
                                     popupTitle,
                                     popupBody,
                                     webUrl,
                                     shouldShowShadow);
            }
                
            WatermarkData WatermarkDataFactory::CreateDefaultEegeo()
            {
                std::string imageAssetName = "eegeo_logo";
                std::string popupTitle = "Maps by WRLD";
                std::string popupBody = "This app is open source. It's built using the WRLD maps SDK, a cross platform API for building engaging, customizable apps.";
                std::string utmSource = m_googleAnalyticsReferrerToken.empty() ? "unspecified" : m_googleAnalyticsReferrerToken;
                std::string webUrl = "http://wrld3d.com/?utm_source=" + utmSource + "&utm_medium=referral&utm_campaign=eegeo";
                
                return Create(imageAssetName,
                              popupTitle,
                              popupBody,
                              webUrl);
            }
        }
    }
}
