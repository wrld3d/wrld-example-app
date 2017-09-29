// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsInFocusModel : public IWorldPinsInFocusModel
            {
            public:
                WorldPinsInFocusModel();

                WorldPinsInFocusModel(int worldPinItemModelId,
                                      const std::string& title,
                                      const std::string& subtitle,
                                      const std::string& vendor,
                                      const std::string& json,
                                      const std::string& ratingsImage,
                                      const int reviewCount,
                                      const int priorityOrder);

                const std::string& GetTitle() const;
                const std::string& GetSubtitle() const;
                const std::string& GetVendor() const;
                const std::string& GetJsonData() const;
                const bool HasRatingsImage() const;
                const std::string& GetRatingsImage() const;
                const int GetReviewCount() const;
                const int GetPinId() const;
                void SetPinId(int worldPinItemModelId);
                const int GetPriorityOrder() const;
                
                void Refresh(const std::string& title, const std::string& subtitle, const std::string& ratingsImage, const int reviewCount);

            private:

                int m_worldPinItemModelId;
                std::string m_title;
                std::string m_subtitle;
                std::string m_vendor;
                std::string m_json;
                std::string m_ratingsImage;
                int m_reviewCount;
                int m_priorityOrder;
            };
        }
    }
}
