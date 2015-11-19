// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WatermarkData.h"

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class IWatermarkDataFactory
            {
            public:
                virtual ~IWatermarkDataFactory() {}
                
                virtual WatermarkData Create(const std::string& imageAssetUrl,
                                             const std::string& popupTitle,
                                             const std::string& popupBody,
                                             const std::string& webUrl,
                                             const bool shouldShowShadow = false) = 0;
                
                virtual WatermarkData CreateDefaultEegeo() = 0;
            };
        }
    }
}