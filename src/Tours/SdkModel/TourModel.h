// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include <string>
#include <vector>
#include "LatLongAltitude.h"
#include "TourStateModel.h"
#include "AppColorHelpers.h"
#include "WorldPinInteriorData.h"
#include "TweetModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            const std::string GenerateTourHovercardJsonData(const TourModel& tourModel);

            class TourModel
            {
                std::string m_name;
                std::string m_introText;
                Eegeo::Space::LatLong m_location;
                std::string m_pinIconKey;
                bool m_isInterior;
                bool m_showGradientBase;
                bool m_visibleOnMap;
                Helpers::ColorHelpers::Color m_baseColor;
                Helpers::ColorHelpers::Color m_textColor;
                Helpers::ColorHelpers::Color m_hoverCardBaseColor;
                Helpers::ColorHelpers::Color m_hoverCardTextColor;
                
                std::vector<TourStateModel> m_states;
                ExampleApp::WorldPins::SdkModel::WorldPinInteriorData m_worldPinInteriorData;
                
                bool m_usesTwitter;
                std::string m_twitterBaseUserName;
                std::string m_twitterBaseProfileImage;
                
            public:
                TourModel();
                
                static TourModel Empty();
                
                TourModel(const std::string& name,
                          const std::string& introText,
                          const std::string& pinIconKey,
                          const Eegeo::Space::LatLong& location,
                          bool visibleOnMap,
                          bool isInterior,
                          const ExampleApp::WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                          bool showGradientBase,
                          Helpers::ColorHelpers::Color baseColor,
                          Helpers::ColorHelpers::Color textColor,
                          Helpers::ColorHelpers::Color hoverCardBaseColor,
                          Helpers::ColorHelpers::Color hoverCardTextColor,
                          const std::vector<TourStateModel>& states,
                          bool usesTwitter = false,
                          const std::string& twitterBaseUserName = "",
                          const std::string& twitterBaseProfileImage = "");
                
                const std::string& Name() const;
                
                const std::string& IntroText() const;
                
                bool IsVisibleOnMap() const;
                
                std::string PinIconKey() const;
                
                const Eegeo::Space::LatLong& Location() const;
                
                bool IsInterior() const;
                
                const ExampleApp::WorldPins::SdkModel::WorldPinInteriorData& WorldPinInteriorData() const;
                
                bool ShowGradientBase() const;
                
                Helpers::ColorHelpers::Color BaseColor() const;
                
                Helpers::ColorHelpers::Color TextColor() const;
                
                Helpers::ColorHelpers::Color HoverCardBaseColor() const;
                
                Helpers::ColorHelpers::Color HoverCardTextColor() const;
                
                const std::vector<TourStateModel>& States() const;
                
                int StateCount() const;
                
                bool UsesTwitter() const;
                
                const std::string& TwitterBaseUserName() const;
                
                const std::string& TwitterBaseProfileImage() const;
            };
            
            inline bool operator==(const TourModel& lhs, const TourModel& rhs)
            {
                return lhs.Name() == rhs.Name();
            }
            inline bool operator!=(const TourModel& lhs, const TourModel& rhs)
            {
                return !operator==(lhs,rhs);
            }
            inline bool operator< (const TourModel& lhs, const TourModel& rhs)
            {
                return lhs.Name() < rhs.Name();
            }
            inline bool operator> (const TourModel& lhs, const TourModel& rhs)
            {
                return  operator< (rhs,lhs);
            }
            inline bool operator<=(const TourModel& lhs, const TourModel& rhs)
            {
                return !operator> (lhs,rhs);
            }
            inline bool operator>=(const TourModel& lhs, const TourModel& rhs)
            {
                return !operator< (lhs,rhs);
            }
        }
    }
}
