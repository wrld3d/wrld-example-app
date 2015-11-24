// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWatermarkDataFactory.h"
#include "WatermarkData.h"

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkDataFactory : public IWatermarkDataFactory
            {
            public:
                WatermarkDataFactory(const std::string& appName,
                                     const std::string& googleAnalyticsReferrerToken);
                
                WatermarkData Create(const std::string& imageAssetUrl,
                                     const std::string& popupTitle,
                                     const std::string& popupBody,
                                     const std::string& webUrl,
                                     const bool shouldShowShadow = false);
                
                WatermarkData CreateDefaultEegeo();
                
            private:
                const std::string m_appName;
                const std::string m_googleAnalyticsReferrerToken;
            };
        }
    }
}