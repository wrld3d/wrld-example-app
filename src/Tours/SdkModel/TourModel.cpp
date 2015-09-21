// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourModel::TourModel()
            : m_name("")
            , m_introText("")
            , m_location(Eegeo::Space::LatLong::FromDegrees(0,0))
            , m_showGradientBase(false)
            , m_baseColor(Helpers::ColorHelpers::Color::FromRGB(0, 0, 0))
            , m_textColor(Helpers::ColorHelpers::Color::FromRGB(0, 0, 0))
            , m_hoverCardBaseColor(Helpers::ColorHelpers::Color::FromRGB(0, 0, 0))
            , m_hoverCardTextColor(Helpers::ColorHelpers::Color::FromRGB(0, 0, 0))
            , m_states()
            , m_isInterior(false)
            {
                
            }
            
            TourModel::TourModel(const std::string& name,
                                 const std::string& introText,
                                 const Eegeo::Space::LatLong& location,
                                 bool isInterior,
                                 const ExampleApp::WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                                 bool showGradientBase,
                                 Helpers::ColorHelpers::Color baseColor,
                                 Helpers::ColorHelpers::Color textColor,
                                 Helpers::ColorHelpers::Color hoverCardBaseColor,
                                 Helpers::ColorHelpers::Color hoverCardTextColor,
                                 const std::vector<TourStateModel>& states)
            : m_name(name)
            , m_introText(introText)
            , m_location(location)
            , m_showGradientBase(showGradientBase)
            , m_baseColor(baseColor)
            , m_textColor(textColor)
            , m_hoverCardBaseColor(hoverCardBaseColor)
            , m_hoverCardTextColor(hoverCardTextColor)
            , m_states(states)
            , m_isInterior(isInterior)
            , m_worldPinInteriorData(worldPinInteriorData)
            {
                
            }
            
            TourModel TourModel::Empty()
            {
                return TourModel();
            }
            
            const std::string& TourModel::Name() const
            {
                return m_name;
            }
            
            const std::string& TourModel::IntroText() const
            {
                return m_introText;
            }
            
            const Eegeo::Space::LatLong& TourModel::Location() const
            {
                return m_location;
            }
            
            bool TourModel::IsInterior() const
            {
                return m_isInterior;
            }
            
            bool TourModel::ShowGradientBase() const
            {
                return m_showGradientBase;
            }
            
            Helpers::ColorHelpers::Color TourModel::BaseColor() const
            {
                return m_baseColor;
            }
            
            Helpers::ColorHelpers::Color TourModel::TextColor() const
            {
                return m_textColor;
            }
            
            Helpers::ColorHelpers::Color TourModel::HoverCardBaseColor() const
            {
                return m_hoverCardBaseColor;
            }
            
            Helpers::ColorHelpers::Color TourModel::HoverCardTextColor() const
            {
                return m_hoverCardTextColor;
            }
            
            const ExampleApp::WorldPins::SdkModel::WorldPinInteriorData& TourModel::WorldPinInteriorData() const
            {
                return m_worldPinInteriorData;
            }
            
            const std::vector<TourStateModel>& TourModel::States() const
            {
                return m_states;
            }
            
            int TourModel::StateCount() const
            {
                return m_states.size();
            }
        }
    }
}
