// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class IWatermarkDataRepository
            {
            public:
                virtual ~IWatermarkDataRepository() { }
                virtual void AddWatermarkData(const std::string& key,
                                              const WatermarkData& watermarkData) = 0;
                
                virtual void RemoveWatermarkDataWithKey(const std::string& key) = 0;
                
                virtual bool HasWatermarkDataForKey(const std::string& key) const = 0;
                virtual WatermarkData GetWatermarkDataWithKey(const std::string& key) const = 0;
    
            };
        }
    }
}