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
                const std::string Name = "name";
                const std::string StartLocationLatitude = "start_location_latitude";
                const std::string StartLocationLongitude = "start_location_longitude";
                const std::string StartLocationAltitude = "start_location_altitude";
                const std::string StartLocationDistance = "start_location_distance";
                const std::string StartLocationOrientationDegrees = "start_location_orientation_degrees";
                const std::string TryStartAtGpsLocation = "try_start_at_gps_location";
                const std::string EegeoApiKey = "eegeo_api_key";
                const std::string CoverageTreeManifestURL = "coveragetree_manifest_url";
                const std::string ThemeManifestURL = "theme_manifest_url";
                const std::string EmbeddedThemeTexturePath = "embedded_theme_texture_path";
                const std::string GoogleAnalyticsReferrerToken = "google_analytics_referrer_token";
                const std::string FlurryAppKey = "flurry_app_key";
                const std::string YelpConsumerKey = "yelp_consumer_key";
                const std::string YelpConsumerSecret = "yelp_consumer_secret";
                const std::string YelpOAuthToken = "yelp_oauth_token";
                const std::string YelpOAuthTokenSecret = "yelp_oauth_token_secret";
                const std::string GeoNamesUserName = "geonames_username";
                const std::string EegeoSearchServiceUrl = "eegeo_search_service_url";
                const std::string MyPinsWebServiceUrl = "mypins_web_service_url";
                const std::string MyPinsWebServiceAuthToken = "mypins_web_service_auth_token";
                const std::string TwitterAuthCode = "twitter_auth_code";
                const std::string IsKioskTouchInputEnabled = "is_kiosk_touch_input_enabled";
                const std::string StartAppInFullscreen = "start_app_in_fullscreen";
                const std::string UseLabels = "use_labels";
                const std::string UseJapaneseFont = "use_japanese_font";
                const std::string IndoorTrackedBuildings = "indoor_tracked_buildings";
                const std::string InteriorId = "interior_id";
                const std::string Type = "type";
                const std::string Config = "config";
                const std::string ApiKey = "api_key";
                const std::string ApiSecret = "api_secret";
                const std::string FloorMapping = "floor_mapping";
                const std::string BuildingFloorIndex = "building_floor_index";
                const std::string TrackedFloorIndex = "tracked_floor_index";
                
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
                
                bool ParseBoolOrDefault(rapidjson::Document& document, const std::string& key, bool defaultValue)
                {
                    if (document.HasMember(key.c_str()))
                    {
                        return document[key.c_str()].GetBool();
                    }
                    return defaultValue;
                }
                
                double ParseDoubleOrDefault(rapidjson::Document& document, const std::string& key, double defaultValue)
                {
                    if (document.HasMember(key.c_str()))
                    {
                        return document[key.c_str()].GetDouble();
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

                const double startLocationLatitude = ParseDoubleOrDefault(document, StartLocationLatitude, m_defaultConfig.InterestLocation().GetLatitudeInDegrees());
                const double startLocationLongitude = ParseDoubleOrDefault(document, StartLocationLongitude, m_defaultConfig.InterestLocation().GetLongitudeInDegrees());
                const double startLocationAltitude = ParseDoubleOrDefault(document, StartLocationAltitude, m_defaultConfig.InterestLocation().GetAltitude());
                const double startLocationDistance = ParseDoubleOrDefault(document, StartLocationDistance, m_defaultConfig.DistanceToInterestMetres());
                const double startLocationOrientationDegrees = ParseDoubleOrDefault(document, StartLocationOrientationDegrees, m_defaultConfig.OrientationDegrees());

                const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(startLocationLatitude,
                                                                                                   startLocationLongitude,
                                                                                                   startLocationAltitude);
                
                const bool tryStartAtGpsLocation = ParseBoolOrDefault(document, TryStartAtGpsLocation, m_defaultConfig.TryStartAtGpsLocation());

                const std::string& name = ParseStringOrDefault(document, Name, m_defaultConfig.Name());
                const std::string& eegeoApiKey = ParseStringOrDefault(document, EegeoApiKey, m_defaultConfig.EegeoApiKey());
                const std::string& coverageTreeManifestURL = ParseStringOrDefault(document, CoverageTreeManifestURL, m_defaultConfig.CoverageTreeManifestURL());
                const std::string& themeManifestURL = ParseStringOrDefault(document, ThemeManifestURL, m_defaultConfig.ThemeManifestURL());
                const std::string& embeddedThemeTexturePath = ParseStringOrDefault(document, EmbeddedThemeTexturePath, m_defaultConfig.EmbeddedThemeTexturePath());
                const std::string& googleAnalyticsReferrerToken = ParseStringOrDefault(document, GoogleAnalyticsReferrerToken, m_defaultConfig.GoogleAnalyticsReferrerToken());
                const std::string& flurryAppKey = ParseStringOrDefault(document, FlurryAppKey, m_defaultConfig.FlurryAppKey());
                const std::string& yelpConsumerKey = ParseStringOrDefault(document, YelpConsumerKey, m_defaultConfig.YelpConsumerKey());
                const std::string& yelpConsumerSecret = ParseStringOrDefault(document, YelpConsumerSecret, m_defaultConfig.YelpConsumerSecret());
                const std::string& yelpOAuthToken = ParseStringOrDefault(document, YelpOAuthToken, m_defaultConfig.YelpOAuthToken());
                const std::string& yelpOAuthTokenSecret = ParseStringOrDefault(document, YelpOAuthTokenSecret, m_defaultConfig.YelpOAuthTokenSecret());
                const std::string& geoNamesUserName = ParseStringOrDefault(document, GeoNamesUserName, m_defaultConfig.GeoNamesUserName());
                const std::string& eegeoSearchServiceUrl = ParseStringOrDefault(document, EegeoSearchServiceUrl, m_defaultConfig.EegeoSearchServiceUrl());
                const std::string& myPinsWebServiceUrl = ParseStringOrDefault(document, MyPinsWebServiceUrl, m_defaultConfig.MyPinsWebServiceUrl());
                const std::string& myPinsWebServiceAuthToken = ParseStringOrDefault(document, MyPinsWebServiceAuthToken, m_defaultConfig.MyPinsWebServiceAuthToken());
                const std::string& twitterAuthCode = ParseStringOrDefault(document, TwitterAuthCode, m_defaultConfig.TwitterAuthCode());
                bool isKioskTouchInputEnabled = ParseBoolOrDefault(document, IsKioskTouchInputEnabled, m_defaultConfig.IsKioskTouchInputEnabled());
                bool startFullscreen = ParseBoolOrDefault(document, StartAppInFullscreen, m_defaultConfig.ShouldStartFullscreen());
                bool useLabels = ParseBoolOrDefault(document, UseLabels, m_defaultConfig.UseLabels());
                bool useJapaneseFont = ParseBoolOrDefault(document, UseJapaneseFont, m_defaultConfig.UseJapaneseFont());

                std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;
                if(document.HasMember(IndoorTrackedBuildings.c_str()) && !document[IndoorTrackedBuildings.c_str()].IsNull())
                {
                    const rapidjson::Value& indoorTrackedBuildingsArray = document[IndoorTrackedBuildings.c_str()];
                    ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
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
                    startLocationDistance,
                    startLocationOrientationDegrees,
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
                    isKioskTouchInputEnabled,
                    useLabels,
                    useJapaneseFont,
                    interiorTrackingInfoList
                );
            }
            
            bool ApplicationConfigurationJsonParser::IsValidConfig(const std::string& serialized)
            {
                rapidjson::Document document;
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                return !hasParseError;
            }
            
            void ApplicationConfigurationJsonParser::ParseIndoorTrackingInfo(std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                                                             const rapidjson::Value& indoorTrackedBuildingsArray)
            {
                for(rapidjson::SizeType i = 0; i < indoorTrackedBuildingsArray.Size(); ++i)
                {
                    const rapidjson::Value& building = indoorTrackedBuildingsArray[i];
                    
                    Eegeo_ASSERT(building.HasMember(InteriorId.c_str()), "Interior Id not found");
                    const std::string& id = building[InteriorId.c_str()].GetString();
                    const Eegeo::Resources::Interiors::InteriorId& interiorId(id);
                    
                    Eegeo_ASSERT(building.HasMember(Type.c_str()), "Type not found");
                    const std::string& type = building[Type.c_str()].GetString();

                    
                    Eegeo_ASSERT(building.HasMember(Config.c_str()), "Config not found");
                    const std::string& apiKey = building[Config.c_str()][0][ApiKey.c_str()].GetString();
                    const std::string& apiSecret = building[Config.c_str()][0][ApiSecret.c_str()].GetString();
                    SdkModel::ApplicationInteriorTrackingConfig interiorTrackingConfig(apiKey, apiSecret);
                    
                    Eegeo_ASSERT(building.HasMember(FloorMapping.c_str()), "FloorMapping not found");
                    const rapidjson::Value& floorMappingArray = building[FloorMapping.c_str()];
                    
                    std::map<int, std::string> floorMapping;
                    for(rapidjson::SizeType j = 0; j < floorMappingArray.Size(); ++j)
                    {
                        floorMapping[floorMappingArray[j][BuildingFloorIndex.c_str()].GetInt()] = floorMappingArray[j][TrackedFloorIndex.c_str()].GetString();
                    }
                    
                    SdkModel::ApplicationInteriorTrackingInfo interiorTrackingInfo(interiorId,
                                                                                   type,
                                                                                   interiorTrackingConfig,
                                                                                   floorMapping);
                    
                    interiorTrackingInfoList.insert(std::pair<std::string, SdkModel::ApplicationInteriorTrackingInfo>(interiorId.Value(),interiorTrackingInfo));
                }
            }
        }
    }
}
