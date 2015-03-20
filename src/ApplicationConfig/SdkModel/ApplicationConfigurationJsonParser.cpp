// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "document.h"
#include "ApplicationConfigurationJsonParser.h"
#include "IApplicationConfigurationBuilder.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationJsonParser::ApplicationConfigurationJsonParser(IApplicationConfigurationBuilder& builder)
            : m_builder(builder)
            {
                
            }
            
            ApplicationConfiguration ApplicationConfigurationJsonParser::ParseConfiguration(const std::string& serialized)
            {
                rapidjson::Document document;
                
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                Eegeo_ASSERT(!hasParseError);
                
                Eegeo_ASSERT(document.HasMember("Name"));
                m_builder.SetApplicationName(document["Name"].GetString());
                
                Eegeo_ASSERT(document.HasMember("StartLocationLatitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationLongitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationAltitude"));
                m_builder.SetStartInterestPointLocation(Eegeo::Space::LatLongAltitude::FromDegrees(document["StartLocationLatitude"].GetDouble(),
                                                                                                   document["StartLocationLongitude"].GetDouble(),
                                                                                                   document["StartLocationAltitude"].GetDouble()));
                
                Eegeo_ASSERT(document.HasMember("StartLocationDistance"));
                m_builder.SetStartDistanceFromInterestPoint(static_cast<float>(document["StartLocationDistance"].GetDouble()));
                
                Eegeo_ASSERT(document.HasMember("StartLocationOrientationDegrees"));
                m_builder.SetStartOrientationAboutInterestPoint(static_cast<float>(document["StartLocationOrientationDegrees"].GetDouble()));
                
                Eegeo_ASSERT(document.HasMember("TryStartAtGpsLocation"));
                m_builder.SetTryStartAtGpsLocation(document["TryStartAtGpsLocation"].GetBool());
                
                return m_builder.Build();
            }
        }
    }
}
