// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            const std::string DefaultEegeoWatermarkId = "eegeo";
            
            class WatermarkModel
            {
            public:
                WatermarkModel()
                : m_id(DefaultEegeoWatermarkId)
                {
                    
                }
                
                std::string GetId() const { return m_id; }
                void SetId(const std::string& newId) { m_id = newId; }
            private:
                std::string m_id;
            };
        }
    }
}