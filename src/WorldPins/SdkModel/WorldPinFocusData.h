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
                WorldPinFocusData(const std::string& title,
                                  const std::string& subtitle,
                                  const std::string& vendor,
                                  const std::string& json,
                                  const std::string& ratingsImg,
                                  const int reviewCount,
                                  const int priorityOrder)
                : title(title)
                , subtitle(subtitle)
                , vendor(vendor)
                , json(json)
                , ratingsImage(ratingsImg)
                , reviewCount(reviewCount)
                , priorityOrder(priorityOrder)
                {

                }
                
                WorldPinFocusData(const std::string& title, const std::string& subtitle, const std::string vendor)
                : title(title)
                , subtitle(subtitle)
                , ratingsImage("")
                , vendor(vendor)
                , json("")
                , reviewCount(0)
                , priorityOrder(0)
                {
                    
                }

                std::string title;
                std::string subtitle;
                std::string vendor;
                std::string json;
                std::string ratingsImage;
                int reviewCount;
                int priorityOrder;
            };
        }
    }
}
