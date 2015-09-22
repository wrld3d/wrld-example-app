// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ColorHelpers
        {
            class Color
            {
                u32 m_value;
                
                Color(u32 value):m_value(value) { }
                
            public:
                Color():m_value(0) { }
                
                static Color FromRGB(Byte red, Byte green, Byte blue)
                {
                    return Color((red << 24) | (green << 16) | (blue << 8));
                }
                
                Byte GetRed() const     { return (m_value & 0xFF000000) >> 24; }
                Byte GetGreen() const   { return (m_value & 0x00FF0000) >> 16;}
                Byte GetBlue() const    { return (m_value & 0x0000FF00) >> 8; }
                
                float GetRedF() const   { return GetRed() / 255.f; }
                float GetGreenF() const { return GetGreen() / 255.f; }
                float GetBlueF() const  { return GetBlue() / 255.f;}
            };
        }
    }
}
