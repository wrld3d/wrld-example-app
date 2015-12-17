// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            struct VisualMapState
            {
            public:
                VisualMapState(const std::string& theme,
                               const std::string& state,
                               bool isFlattened)
                : m_theme(theme)
                , m_state(state)
                , m_isFlattened(isFlattened)
                {
                    
                }
                
                std::string GetTheme() const { return m_theme; }
                std::string GetState() const { return m_state; }
                bool IsFlattened() const { return m_isFlattened; }
                
            private:
                std::string m_theme;
                std::string m_state;
                bool m_isFlattened;
            };
        }
    }
}