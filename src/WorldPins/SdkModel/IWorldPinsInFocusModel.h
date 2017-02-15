// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsInFocusModel
            {
            public:
                virtual ~IWorldPinsInFocusModel() { }

                virtual const std::string& GetTitle() const = 0;
                virtual const std::string& GetSubtitle() const = 0;
                virtual const std::string& GetVendor() const = 0;
                virtual const std::string& GetJsonData() const = 0;
                virtual const bool HasRatingsImage() const = 0;
                virtual const std::string& GetRatingsImage() const = 0;
                virtual const int GetReviewCount() const = 0;
                virtual const int GetPinId() const = 0;
                virtual const int GetPriorityOrder() const = 0;
                
                virtual void Refresh(const std::string& title, const std::string& subtitle, const std::string& ratingsImage, const int reviewCount) = 0;
            };
        }
    }
}
