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
                    if (document.HasMember(key.c_str()))
                    {
                        const std::string& value = document[key.c_str()].GetString();
                        if (!value.empty())
                        {
                            return value;
                        }
                    }
                    return defaultValue;
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
                Eegeo_ASSERT(!hasParseError, "unable to parse app configuration");

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
                const std::string& eegeoApiKey = ParseStringOrDefault(document, "EegeoApiKey", m_defaultConfig.EegeoApiKey());                
                const std::string& coverageTreeManifestURL = ParseStringOrDefault(document, "CoverageTreeManifestURL", m_defaultConfig.CoverageTreeManifestURL());
                const std::string& themeManifestURL = ParseStringOrDefault(document, "ThemeManifestURL", m_defaultConfig.ThemeManifestURL());
                const std::string& embeddedThemeTexturePath = ParseStringOrDefault(document, "EmbeddedThemeTexturePath", m_defaultConfig.EmbeddedThemeTexturePath());
                const std::string& googleAnalyticsReferrerToken = ParseStringOrDefault(document, "GoogleAnalyticsReferrerToken", m_defaultConfig.GoogleAnalyticsReferrerToken());
                const std::string& flurryAppKey = ParseStringOrDefault(document, "FlurryAppKey", m_defaultConfig.FlurryAppKey());
                const std::string& yelpConsumerKey = ParseStringOrDefault(document, "YelpConsumerKey", m_defaultConfig.YelpConsumerKey());
                const std::string& yelpConsumerSecret = ParseStringOrDefault(document, "YelpConsumerSecret", m_defaultConfig.YelpConsumerSecret());
                const std::string& yelpOAuthToken = ParseStringOrDefault(document, "YelpOAuthToken", m_defaultConfig.YelpOAuthToken());
                const std::string& yelpOAuthTokenSecret = ParseStringOrDefault(document, "YelpOAuthTokenSecret", m_defaultConfig.YelpOAuthTokenSecret());
                const std::string& geoNamesUserName = ParseStringOrDefault(document, "GeoNamesUserName", m_defaultConfig.GeoNamesUserName());
                const std::string& eegeoSearchServiceUrl = ParseStringOrDefault(document, "EegeoSearchServiceUrl", m_defaultConfig.EegeoSearchServiceUrl());
                const std::string& myPinsWebServiceUrl = ParseStringOrDefault(document, "MyPinsWebServiceUrl", m_defaultConfig.MyPinsWebServiceUrl());
                const std::string& myPinsWebServiceAuthToken = ParseStringOrDefault(document, "MyPinsWebServiceAuthToken", m_defaultConfig.MyPinsWebServiceAuthToken());
                const std::string& twitterAuthCode = ParseStringOrDefault(document, "TwitterAuthCode", m_defaultConfig.TwitterAuthCode());

                bool isKioskTouchInputEnabled = false;
                if (document.HasMember("IsKioskTouchInputEnabled") && !document["IsKioskTouchInputEnabled"].IsNull())
                {
                    isKioskTouchInputEnabled = document["IsKioskTouchInputEnabled"].GetBool();
                }

                bool startFullscreen = false;

                if (document.HasMember("StartAppInFullscreen") && !document["StartAppInFullscreen"].IsNull())
                {
                    startFullscreen = document["StartAppInFullscreen"].GetBool();
                }

                return ApplicationConfiguration(
                    name,
                    eegeoApiKey,
                    m_defaultConfig.ProductVersion(),
                    m_defaultConfig.BuildNumber(),
                    m_defaultConfig.CombinedVersionString(),
                    coverageTreeManifestURL,
                    themeManifestURL,
                    embeddedThemeTexturePath,
                    lla,
                    startDistanceFromInterestPoint,
                    startOrientationAboutInterestPoint,
                    tryStartAtGpsLocation,
                    startFullscreen,
                    googleAnalyticsReferrerToken,
                    flurryAppKey,
                    yelpConsumerKey,
                    yelpConsumerSecret,
                    yelpOAuthToken,
                    yelpOAuthTokenSecret,
                    geoNamesUserName,
                    eegeoSearchServiceUrl,
                    myPinsWebServiceUrl,
                    myPinsWebServiceAuthToken,
                    twitterAuthCode,
                    isKioskTouchInputEnabled
                );
            }
        }
    }
}
