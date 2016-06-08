// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "document.h"
#include "ApplicationConfigurationJsonParser.h"
#include "MathFunc.h"
#include "ConfigSections.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                std::string ParseStringOrDefault(rapidjson::Document& document, const std::string& key, const std::string& defaultValue)
                {
                    return (document.HasMember(key.c_str()))
                        ? document[key.c_str()].GetString()
                        : defaultValue;
                }
            }

            ApplicationConfigurationJsonParser::ApplicationConfigurationJsonParser(const ApplicationConfiguration& defaultConfig)
            : m_defaultConfig(defaultConfig)
            {
                
            }
            
            ApplicationConfiguration ApplicationConfigurationJsonParser::ParseConfiguration(const std::string& serialized)
            {
                rapidjson::Document document;
                
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                Eegeo_ASSERT(!hasParseError);
                
                Eegeo_ASSERT(document.HasMember("StartLocationLatitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationLongitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationAltitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationDistance"));
                Eegeo_ASSERT(document.HasMember("StartLocationOrientationDegrees"));
                Eegeo_ASSERT(document.HasMember("TryStartAtGpsLocation"));

                
                const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(document["StartLocationLatitude"].GetDouble(),
                                                                                                   document["StartLocationLongitude"].GetDouble(),
                                                                                                   document["StartLocationAltitude"].GetDouble());
                
                const float startDistanceFromInterestPoint = static_cast<float>(document["StartLocationDistance"].GetDouble());
                const float startOrientationAboutInterestPoint = static_cast<float>(document["StartLocationOrientationDegrees"].GetDouble());
                const bool tryStartAtGpsLocation = document["TryStartAtGpsLocation"].GetBool();

                const std::string& name = ParseStringOrDefault(document, "Name", m_defaultConfig.Name());
                const std::string& googleAnalyticsReferrerToken = ParseStringOrDefault(document, "GoogleAnalyticsReferrerToken", m_defaultConfig.GoogleAnalyticsReferrerToken());
                const std::string& coverageTreeManifestURL = ParseStringOrDefault(document, "CoverageTreeManifestURL", m_defaultConfig.CoverageTreeManifestURL());
                const std::string& themeManifestURL = ParseStringOrDefault(document, "ThemeManifestURL", m_defaultConfig.ThemeManifestURL());

                return ApplicationConfiguration(
                    name,
                    lla,
                    startDistanceFromInterestPoint,
                    startOrientationAboutInterestPoint,
                    tryStartAtGpsLocation,
                    googleAnalyticsReferrerToken,
                    m_defaultConfig.ProductVersion(),
                    m_defaultConfig.BuildNumber(),
                    m_defaultConfig.CombinedVersionString(),
                    coverageTreeManifestURL,
                    themeManifestURL
                );
            }
        }
    }
}
