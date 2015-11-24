// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWatermarkDataRepository.h"
#include "Watermark.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkDataRepository : public IWatermarkDataRepository
            {
            public:
                void AddWatermarkData(const std::string& key,
                                      const WatermarkData& watermarkData);
                
                void RemoveWatermarkDataWithKey(const std::string& key);
                
                bool HasWatermarkDataForKey(const std::string& key) const;
                WatermarkData GetWatermarkDataWithKey(const std::string& key) const;
                
            private:
                typedef std::map<std::string, WatermarkData> TWatermarkDataMap;
                TWatermarkDataMap m_watermarkDataMap;
            };
        }
    }
}