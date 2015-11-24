// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        class WatermarkModelChangedMessage
        {
        public:
            WatermarkModelChangedMessage(const std::string& watermarkId)
            : m_watermarkId(watermarkId)
            {
            }
            
            std::string GetWatermarkId() const { return m_watermarkId; }
            
        private:
            std::string m_watermarkId;
        };
    }
}
