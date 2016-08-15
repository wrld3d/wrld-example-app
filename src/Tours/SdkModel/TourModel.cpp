// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourModel.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            const std::string GenerateTourHovercardJsonData(const TourModel& tourModel)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Value valueObject(rapidjson::kObjectType);
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                
                if(!tourModel.UsesTwitter())
                {
                    const Helpers::ColorHelpers::Color& baseColor = tourModel.HoverCardBaseColor();
                    const Helpers::ColorHelpers::Color& textColor = tourModel.HoverCardTextColor();
                    
                    rapidjson::Value baseColorObject(rapidjson::kObjectType);
                    rapidjson::Value textColorObject(rapidjson::kObjectType);
                    std::string jsonString ="";
                    
                    baseColorObject.AddMember("r", static_cast<int>(baseColor.GetRed()), allocator);
                    baseColorObject.AddMember("g", static_cast<int>(baseColor.GetGreen()), allocator);
                    baseColorObject.AddMember("b", static_cast<int>(baseColor.GetBlue()), allocator);
                    
                    textColorObject.AddMember("r", static_cast<int>(textColor.GetRed()), allocator);
                    textColorObject.AddMember("g", static_cast<int>(textColor.GetGreen()), allocator);
                    textColorObject.AddMember("b", static_cast<int>(textColor.GetBlue()), allocator);
                    
                    valueObject.AddMember("base_col", baseColorObject, allocator);
                    valueObject.AddMember("text_col", textColorObject, allocator);
                }
                else
                {
                    valueObject.AddMember("twitter_image", rapidjson::Value(tourModel.TwitterBaseProfileImage().c_str(), allocator).Move(), allocator);
                }
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                return strbuf.GetString();
            }
            
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
            , m_worldPinInteriorData()
            , m_usesTwitter(false)
            , m_twitterBaseUserName("")
            , m_twitterBaseProfileImage("")
            {
                
            }
            
            TourModel::TourModel(const std::string& name,
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
                                 bool usesTwitter,
                                 const std::string& twitterBaseUserName,
                                 const std::string& twitterBaseProfileImage)
            : m_name(name)
            , m_introText(introText)
            , m_pinIconKey(pinIconKey)
            , m_location(location)
            , m_visibleOnMap(visibleOnMap)
            , m_showGradientBase(showGradientBase)
            , m_baseColor(baseColor)
            , m_textColor(textColor)
            , m_hoverCardBaseColor(hoverCardBaseColor)
            , m_hoverCardTextColor(hoverCardTextColor)
            , m_states(states)
            , m_isInterior(isInterior)
            , m_worldPinInteriorData(worldPinInteriorData)
            , m_usesTwitter(usesTwitter)
            , m_twitterBaseUserName(twitterBaseUserName)
            , m_twitterBaseProfileImage(twitterBaseProfileImage)
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
            
            std::string TourModel::PinIconKey() const
            {
                return m_pinIconKey;
            }
            
            const Eegeo::Space::LatLong& TourModel::Location() const
            {
                return m_location;
            }
            
            bool TourModel::IsVisibleOnMap() const
            {
                return m_visibleOnMap;
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
                return static_cast<int>(m_states.size());
            }
            
            bool TourModel::UsesTwitter() const
            {
                return m_usesTwitter;
            }
            
            const std::string& TourModel::TwitterBaseUserName() const
            {
                return m_twitterBaseUserName;
            }
            
            const std::string& TourModel::TwitterBaseProfileImage() const
            {
                return m_twitterBaseProfileImage;
            }
        }
    }
}
