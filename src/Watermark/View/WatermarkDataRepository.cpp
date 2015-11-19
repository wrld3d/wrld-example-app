// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkDataRepository.h"
#include "WatermarkData.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            void WatermarkDataRepository::AddWatermarkData(const std::string& key,
                                                           const WatermarkData& watermarkData)
            {
                Eegeo_ASSERT(!(HasWatermarkDataForKey(key)), "Already have watermark data with key %s", key.c_str());
                
                m_watermarkDataMap[key] = watermarkData;
            }
            
            void WatermarkDataRepository::RemoveWatermarkDataWithKey(const std::string& key)
            {
                Eegeo_ASSERT(HasWatermarkDataForKey(key), "Couldn't find watermark data for key %s", key.c_str());
                
                m_watermarkDataMap.erase(key);
            }
            
            bool WatermarkDataRepository::HasWatermarkDataForKey(const std::string& key) const
            {
                return m_watermarkDataMap.find(key) != m_watermarkDataMap.end();
            }
            
            WatermarkData WatermarkDataRepository::GetWatermarkDataWithKey(const std::string& key) const
            {
                Eegeo_ASSERT(HasWatermarkDataForKey(key), "Couldn't find watermark data for key %s", key.c_str());
                
                return m_watermarkDataMap.at(key);
            }
        }
    }
}