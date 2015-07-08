// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            struct WorldPinFocusData
            {
                WorldPinFocusData(const std::string& title, const std::string& subtitle, const std::string ratingsImg, const int reviewCount)
                    : title(title)
                    , subtitle(subtitle)
                    , ratingsImage(ratingsImg)
                    , reviewCount(reviewCount)
                {

                }
                
                WorldPinFocusData(const std::string& title, const std::string& subtitle)
                : title(title)
                , subtitle(subtitle)
                , ratingsImage("")
                , reviewCount(0)
                {
                    
                }

                std::string title;
                std::string subtitle;
                std::string ratingsImage;
                int reviewCount;
            };
        }
    }
}
