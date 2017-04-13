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
                struct CaseInsensitiveCompare
                {
                    bool operator()(const std::string& l, const std::string& r) const
                    {
                        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end(),
                                                            [](const char c1, const char c2)
                                                            {
                                                                return std::tolower(c1) < std::tolower(c2);
                                                            });
                    }
                };

                typedef std::map<std::string, WatermarkData, CaseInsensitiveCompare> TWatermarkDataMap;
                TWatermarkDataMap m_watermarkDataMap;
            };
        }
    }
}