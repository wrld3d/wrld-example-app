// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsInFocusModel::WorldPinsInFocusModel()
                : m_worldPinItemModelId(-1)
            {

            }

            WorldPinsInFocusModel::WorldPinsInFocusModel(int worldPinItemModelId,
                    const std::string& title,
                    const std::string& subtitle,
                    const std::string& vendor,
                    const std::string& json,
                    const std::string& ratingsImage,
                    const int reviewCount,
                    const bool forInteriorTransition)

                : m_worldPinItemModelId(worldPinItemModelId)
                , m_title(title)
                , m_subtitle(subtitle)
                , m_vendor(vendor)
                , m_json(json)
                , m_ratingsImage(ratingsImage)
                , m_reviewCount(reviewCount)
                , m_forInteriorTransition(forInteriorTransition)
            {

            }

            const std::string& WorldPinsInFocusModel::GetTitle() const
            {
                return m_title;
            }

            const std::string& WorldPinsInFocusModel::GetSubtitle() const
            {
                return m_subtitle;
            }
            
            const std::string& WorldPinsInFocusModel::GetVendor() const
            {
                return m_vendor;
            }
            
            const std::string& WorldPinsInFocusModel::GetJsonData() const
            {
                return m_json;
            }

            const bool WorldPinsInFocusModel::HasRatingsImage() const
            {
                return !m_ratingsImage.empty();
            }
            
            const std::string& WorldPinsInFocusModel::GetRatingsImage() const
            {
                return m_ratingsImage;
            }
            
            const int WorldPinsInFocusModel::GetReviewCount() const
            {
                return m_reviewCount;
            }

            const int WorldPinsInFocusModel::GetPinId() const
            {
                return m_worldPinItemModelId;
            }
            
            const bool WorldPinsInFocusModel::isInteriorTransition() const
            {
                return m_forInteriorTransition;
            }

            void WorldPinsInFocusModel::Refresh(const std::string& title, const std::string& subtitle, const std::string& ratingsImage, const int reviewCount)
            {
                m_title = title;
                m_subtitle = subtitle;
                m_ratingsImage = ratingsImage;
                m_reviewCount = reviewCount;
            }
        }
    }
}
