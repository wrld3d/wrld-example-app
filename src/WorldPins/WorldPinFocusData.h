// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        struct WorldPinFocusData
        {
            WorldPinFocusData(const std::string& title, const std::string& subtitle)
            : m_title(title)
            , m_subtitle(subtitle)
            {
                
            }
            
            std::string m_title;
            std::string m_subtitle;
        };
    }
}