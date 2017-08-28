// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "document.h"
#include "ApplicationConfigurationJsonParser.h"
#include "MathFunc.h"
#include "ConfigSections.h"
#include "StringHelpers.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                static const double DefaultAttractModePlaybackSpeed = 0.03;
                const std::string Encrypted = "Encrypted";
                const std::string HMAC_SHA1 = "HMAC_SHA1";
                const std::string Name = "name";
                const std::string StartLocationLatitude = "start_location_latitude";
                const std::string StartLocationLongitude = "start_location_longitude";
                const std::string StartLocationAltitude = "start_location_altitude";
                const std::string StartLocationDistance = "start_location_distance";
                const std::string StartLocationOrientationDegrees = "start_location_orientation_degrees";
                const std::string StartLocationIndoorId = "start_location_indoor_id";
                const std::string StartLocationFloorIndex = "start_location_floor_index";
                const std::string TryStartAtGpsLocation = "try_start_at_gps_location";
                const std::string PerformStartUpSearch = "perform_start_up_search";
                const std::string StartUpSearchTag = "start_up_search_tag";
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
                const std::string SqliteDbUrl = "sqlite_db_url";
                const std::string EegeoSearchServiceUrl = "eegeo_search_service_url";
                const std::string MyPinsWebServiceUrl = "mypins_web_service_url";
                const std::string MyPinsWebServiceAuthToken = "mypins_web_service_auth_token";
                const std::string TwitterAuthCode = "twitter_auth_code";
                const std::string IsInKioskMode = "is_in_kiosk_mode";
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
                const std::string WebProxyEnabled = "web_proxy_enabled";
                const std::string WebProxyIgnorePattern = "web_proxy_ignore_pattern";
                const std::string WebProxyIpAddress = "web_proxy_ip_address";
                const std::string WebProxyPort = "web_proxy_port";
                const std::string SSLEnabled = "ssl_enabled";
                const std::string SSLIgnorePattern = "ssl_ignore_pattern";
                const std::string BuildingsSearchViewLocation = "buildings_search_view_location";
                const std::string Latitude = "latitude";
                const std::string Longitude = "longitude";
                const std::string Altitude = "altitude";
                const std::string DistanceToInterest = "distance_to_interest";
                const std::string OrientationDegrees = "orientation_degrees";
                const std::string FloorIndex = "floor_index";
                const std::string WifiRestrictedBuildings = "wifi_restricted_buildings";
                const std::string AllowedSSIDs = "allowed_ssids";
                const std::string CompassCameraOffset = "compass_camera_offset";
                const std::string Offset = "offset";
                const std::string OffsetTopDown = "offset_top_down";
                const std::string CompassCameraDampingEnabled = "compass_camera_damping_enabled";
                const std::string AttractModeTimeout = "attract_mode_timeout";
                const std::string AttractModePositionSpline = "attract_mode_position_spline";
                const std::string AttractModeTargetSpline = "attract_mode_target_spline";
                const std::string AttractModePlaybackSpeed = "attract_mode_playback_speed";
                const std::string FixedIndoorLocation = "fixed_indoor_location";
                const std::string OptionsAdminPassword = "options_admin_password";
                const std::string CustomKeyboardLayout = "custom_keyboard_layout";
                
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
                        if(document[key.c_str()].IsBool())
                        {
                            return document[key.c_str()].GetBool();
                        }
                        else if(document[key.c_str()].IsString())
                        {
                            std::string documentString = document[key.c_str()].GetString();
                            if(documentString == "true")
                            {
                                return true;
                            }
                            else if(documentString == "false")
                            {
                                return false;
                            }
                        }
                    }
                    return defaultValue;
                }
                
                double ParseDoubleOrDefault(rapidjson::Document& document, const std::string& key, double defaultValue)
                {
                    if (document.HasMember(key.c_str()))
                    {
                        if(document[key.c_str()].IsNumber())
                        {
                            return document[key.c_str()].GetDouble();
                        }
                        else if(document[key.c_str()].IsString())
                        {
                            double valueFromString;
                            if(Eegeo::Helpers::TryParseDouble(document[key.c_str()].GetString(), valueFromString))
                            {
                                return valueFromString;
                            }
                        }
                    }
                    return defaultValue;
                }
                
                int ParseIntOrDefault(rapidjson::Document& document, const std::string& key, int defaultValue)
                {
                    if (document.HasMember(key.c_str()))
                    {
                        if(document[key.c_str()].IsInt())
                        {
                            return document[key.c_str()].GetInt();
                        }
                        else if(document[key.c_str()].IsString())
                        {
                            int valueFromString;
                            if(Eegeo::Helpers::TryParseInt(document[key.c_str()].GetString(), valueFromString))
                            {
                                return valueFromString;
                            }
                        }
                    }
                    return defaultValue;
                }

                std::vector<std::vector<std::string>> ParseCustomKeyboardLayout(rapidjson::Document& document, const std::string& customKeyboard)
                {
                    std::vector<std::vector<std::string>> customKeyboardLayout;

                    if(document.HasMember(customKeyboard.c_str()) && document[customKeyboard.c_str()].IsArray())
                    {
                        for (rapidjson::SizeType i = 0; i < document[customKeyboard.c_str()].Size(); ++i)
                        {
                            if (document[customKeyboard.c_str()][i].HasMember("row") && document[customKeyboard.c_str()][i]["row"].IsString() &&
                                document[customKeyboard.c_str()][i].HasMember("index") && document[customKeyboard.c_str()][i]["index"].IsInt() &&
                                document[customKeyboard.c_str()][i].HasMember("lowercase") && document[customKeyboard.c_str()][i]["lowercase"].IsString() &&
                                document[customKeyboard.c_str()][i].HasMember("uppercase") && document[customKeyboard.c_str()][i]["uppercase"].IsString())
                            {
                                std::vector<std::string> customKeyLayout = {
                                    document[customKeyboard.c_str()][i]["row"].GetString(),
                                    std::to_string(document[customKeyboard.c_str()][i]["index"].GetInt()),
                                    document[customKeyboard.c_str()][i]["lowercase"].GetString(),
                                    document[customKeyboard.c_str()][i]["uppercase"].GetString()
                                };
                                customKeyboardLayout.push_back(customKeyLayout);
                            }
                        }
                    }
                    return customKeyboardLayout;
                }
            }

            ApplicationConfigurationJsonParser::ApplicationConfigurationJsonParser(const ApplicationConfiguration& defaultConfig,
                                                                                   IApplicationConfigurationBuilder& builder)
            : m_defaultConfig(defaultConfig)
            , m_builder(builder)
            {
                
            }
            
            ApplicationConfiguration ApplicationConfigurationJsonParser::ParseConfiguration(const std::string& serialized)
            {
                rapidjson::Document document;
                
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                Eegeo_ASSERT(!hasParseError);

                if (document.HasMember(Encrypted.c_str()))
                {
                    Eegeo_ASSERT(document.HasMember(HMAC_SHA1.c_str()), "must have HMAC_SHA1 digest field if Encrypted field is present");
                    
                    const std::string& encryptedValue = document[Encrypted.c_str()].GetString();
                    const std::string& digest = document[HMAC_SHA1.c_str()].GetString();

                    const std::string& decrypted = m_builder.Decrypt(encryptedValue);
                    const bool validHMAC = m_builder.ValidateHMAC(decrypted, digest);
                    Eegeo_ASSERT(validHMAC, "HMAC_SHA1 digest does not match, check that app secret matches that used to encrypt app config");

                    document.Parse<0>(decrypted.c_str());

                    Eegeo_ASSERT(!document.HasParseError(), "unable to parse Encrypted config field");
                }

                m_builder.SetProductVersion(m_defaultConfig.ProductVersion());
                m_builder.SetBuildNumber(m_defaultConfig.BuildNumber());

                m_builder.SetApplicationName(ParseStringOrDefault(document, Name, m_defaultConfig.Name()));
                m_builder.SetEegeoApiKey(ParseStringOrDefault(document, EegeoApiKey, m_defaultConfig.EegeoApiKey()));
                
                m_builder.SetStartInterestPointLocation(Eegeo::Space::LatLongAltitude::FromDegrees(ParseDoubleOrDefault(document, StartLocationLatitude, m_defaultConfig.InterestLocation().GetLatitudeInDegrees()),
                    ParseDoubleOrDefault(document, StartLocationLongitude, m_defaultConfig.InterestLocation().GetLongitudeInDegrees()),
                    ParseDoubleOrDefault(document, StartLocationAltitude, m_defaultConfig.InterestLocation().GetAltitude())));

                m_builder.SetStartDistanceFromInterestPoint(static_cast<float>(ParseDoubleOrDefault(document, StartLocationDistance, m_defaultConfig.DistanceToInterestMetres())));
                m_builder.SetStartOrientationAboutInterestPoint(static_cast<float>(ParseDoubleOrDefault(document, StartLocationOrientationDegrees, m_defaultConfig.OrientationDegrees())));

                m_builder.SetTryStartAtGpsLocation(ParseBoolOrDefault(document, TryStartAtGpsLocation, m_defaultConfig.TryStartAtGpsLocation()));
                
                m_builder.SetPerformStartupSearch(ParseBoolOrDefault(document, PerformStartUpSearch, m_defaultConfig.ShouldPerformStartUpSearch()));
                m_builder.SetStartupSearchTag(ParseStringOrDefault(document, StartUpSearchTag, m_defaultConfig.StartUpSearchTag()));
                
                m_builder.SetGoogleAnalyticsReferrerToken(ParseStringOrDefault(document, GoogleAnalyticsReferrerToken, m_defaultConfig.GoogleAnalyticsReferrerToken()));
                m_builder.SetFlurryAppKey(ParseStringOrDefault(document, FlurryAppKey, m_defaultConfig.FlurryAppKey()));
                
                m_builder.SetYelpConsumerKey(ParseStringOrDefault(document, YelpConsumerKey, m_defaultConfig.YelpConsumerKey()));
                m_builder.SetYelpConsumerSecret(ParseStringOrDefault(document, YelpConsumerSecret, m_defaultConfig.YelpConsumerSecret()));
                m_builder.SetYelpOAuthToken(ParseStringOrDefault(document, YelpOAuthToken, m_defaultConfig.YelpOAuthToken()));
                m_builder.SetYelpOAuthTokenSecret(ParseStringOrDefault(document, YelpOAuthTokenSecret, m_defaultConfig.YelpOAuthTokenSecret()));
                
                m_builder.SetGeoNamesUserName(ParseStringOrDefault(document, GeoNamesUserName, m_defaultConfig.GeoNamesUserName()));
                
                m_builder.SetCoverageTreeManifestURL(ParseStringOrDefault(document, CoverageTreeManifestURL, m_defaultConfig.CoverageTreeManifestURL()));
                m_builder.SetThemeManifestURL(ParseStringOrDefault(document, ThemeManifestURL, m_defaultConfig.ThemeManifestURL()));
                
                m_builder.SetSqliteDbUrl(ParseStringOrDefault(document, SqliteDbUrl, m_defaultConfig.SqliteDbUrl()));
                
                m_builder.SetSearchServiceUrl(ParseStringOrDefault(document, EegeoSearchServiceUrl, m_defaultConfig.EegeoSearchServiceUrl()));
                
                m_builder.SetMyPinsWebServiceUrl(ParseStringOrDefault(document, MyPinsWebServiceUrl, m_defaultConfig.MyPinsWebServiceUrl()));
                m_builder.SetMyPinsWebServiceAuthToken(ParseStringOrDefault(document, MyPinsWebServiceAuthToken, m_defaultConfig.MyPinsWebServiceAuthToken()));
                
                m_builder.SetWebProxyEnabled(ParseBoolOrDefault(document, WebProxyEnabled, m_defaultConfig.WebProxyEnabled()));
                m_builder.SetWebProxyIpAddress(ParseStringOrDefault(document, WebProxyIpAddress, m_defaultConfig.WebProxyIpAddress()));
                m_builder.SetWebProxyPort(ParseIntOrDefault(document, WebProxyPort, m_defaultConfig.WebProxyPort()));

                if (document.HasMember(WebProxyIgnorePattern.c_str()))
                {
                    m_builder.SetWebProxyIgnorePattern(document[WebProxyIgnorePattern.c_str()].GetString());
                }
                
                m_builder.SetSSLEnabled(ParseBoolOrDefault(document, SSLEnabled, m_defaultConfig.SSLEnabled()));
                
                if (document.HasMember(SSLIgnorePattern.c_str()))
                {
                    m_builder.SetSSLIgnorePattern(document[SSLIgnorePattern.c_str()].GetString());
                }
                
                std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*> restrictedBuildingModelArray;
                
                if (document.HasMember(WifiRestrictedBuildings.c_str()))
                {
                    const rapidjson::Value& restrictedBuildingJsonArray = document[WifiRestrictedBuildings.c_str()];
                    for (rapidjson::SizeType i = 0; i < restrictedBuildingJsonArray.Size(); i++)
                    {
                        const rapidjson::Value& restrictedBuilding = restrictedBuildingJsonArray[i];

                        Eegeo_ASSERT(restrictedBuilding.HasMember(InteriorId.c_str()), "InteriorId config not found");
                        std::string interiorId = restrictedBuilding[InteriorId.c_str()].GetString();

                        const rapidjson::Value& allowedWifiIDsJsonArray = restrictedBuilding[AllowedSSIDs.c_str()];
                        std::vector<std::string> allowedWifiIDsModelArray;
                        for (rapidjson::SizeType i = 0; i < allowedWifiIDsJsonArray.Size(); i++)
                        {
                            std::string allowedWifiId =  allowedWifiIDsJsonArray[i].GetString();
                            allowedWifiIDsModelArray.push_back(allowedWifiId);

                        }
                        ExampleApp::ApplicationConfig::RestrictedBuildingInfo *restricitedBuildingInfo = Eegeo_NEW(ExampleApp::ApplicationConfig::RestrictedBuildingInfo)(interiorId, allowedWifiIDsModelArray);
                        restrictedBuildingModelArray.push_back(restricitedBuildingInfo);
                    }
                }
                
                m_builder.SetRestrictedBuildingInfoArray(restrictedBuildingModelArray);

                if (document.HasMember(IsKioskTouchInputEnabled.c_str()) && !document[IsKioskTouchInputEnabled.c_str()].IsNull())
                {
                    m_builder.SetIsKioskTouchInputEnabled(document[IsKioskTouchInputEnabled.c_str()].GetBool());
                }

                if (document.HasMember(IsInKioskMode.c_str()) && !document[IsInKioskMode.c_str()].IsNull())
                {
					m_builder.SetIsInKioskMode(document[IsInKioskMode.c_str()].GetBool());
                }

                if (document.HasMember(StartAppInFullscreen.c_str()) && !document[StartAppInFullscreen.c_str()].IsNull())
                {
                    m_builder.SetShouldStartFullscreen(document[StartAppInFullscreen.c_str()].GetBool());
                }

                m_builder.SetEmbeddedThemeTexturePath(ParseStringOrDefault(document, EmbeddedThemeTexturePath, m_defaultConfig.EmbeddedThemeTexturePath()));

                m_builder.SetTwitterAuthCode(ParseStringOrDefault(document, TwitterAuthCode, m_defaultConfig.TwitterAuthCode()));
                
                const std::string& startLocationIndoorId = ParseStringOrDefault(document, StartLocationIndoorId, m_defaultConfig.IndoorId());
                m_builder.SetIndoorId(startLocationIndoorId);
                
                const int startLocationFloorIndex = ParseIntOrDefault(document, StartLocationFloorIndex, m_defaultConfig.FloorIndex());
                m_builder.SetFloorIndex(startLocationFloorIndex);

                if (document.HasMember(UseLabels.c_str()) && !document[UseLabels.c_str()].IsNull())
                {
                    m_builder.SetUseLabels(document[UseLabels.c_str()].GetBool());
                }

                std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;
                if(document.HasMember(IndoorTrackedBuildings.c_str()) && !document[IndoorTrackedBuildings.c_str()].IsNull())
                {
                    const rapidjson::Value& indoorTrackedBuildingsArray = document[IndoorTrackedBuildings.c_str()];
                    ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
                    m_builder.SetInteriorTrackingInfo(interiorTrackingInfoList);
                }

                m_builder.SetAttractModeTimeoutMs(document.HasMember(AttractModeTimeout.c_str()) ? document[AttractModeTimeout.c_str()].GetInt() : 0);
                if(document.HasMember(AttractModeTargetSpline.c_str()))
                {
                    m_builder.SetAttractModeTargetSplinePoints(ParseLatLongAltitudeArray(document[AttractModeTargetSpline.c_str()]));
                }

                if(document.HasMember(AttractModePositionSpline.c_str()))
                {
                    m_builder.SetAttractModePositionSplinePoints(ParseLatLongAltitudeArray(document[AttractModePositionSpline.c_str()]));
                }

                m_builder.SetAttractModePlaybackSpeed(document.HasMember(AttractModePlaybackSpeed.c_str())
                    ? document[AttractModePlaybackSpeed.c_str()].GetDouble()
                    : DefaultAttractModePlaybackSpeed);

                if (document.HasMember(BuildingsSearchViewLocation.c_str()))
                {
                    m_builder.SetBuildingsSearchViewLocationAvailable(true);
                    Eegeo::Space::LatLongAltitude latLongAltitude = ParseLatLongAltitude(document[BuildingsSearchViewLocation.c_str()]);
                    Eegeo_ASSERT(document[BuildingsSearchViewLocation.c_str()].HasMember(DistanceToInterest.c_str()), "BuildingsSearchViewLocation, DistanceToInterest not found");
                    float distanceToInterest = static_cast<float>(document[BuildingsSearchViewLocation.c_str()][DistanceToInterest.c_str()].GetDouble());
                    Eegeo_ASSERT(document[BuildingsSearchViewLocation.c_str()].HasMember(OrientationDegrees.c_str()), "BuildingsSearchViewLocation, OrientationDegrees not found");
                    float orientationDegrees = static_cast<float>(document[BuildingsSearchViewLocation.c_str()][OrientationDegrees.c_str()].GetDouble());
                    m_builder.SetBuildingsSearchViewLocation(latLongAltitude, distanceToInterest, orientationDegrees);
                }

                if(document.HasMember(FixedIndoorLocation.c_str()))
                {
                    ParseFixedIndoorLocation(document[FixedIndoorLocation.c_str()]);
                }

                m_builder.SetAdminPassword(ParseStringOrDefault(document, OptionsAdminPassword.c_str(), ""));

                const std::vector<std::vector<std::string>> customKeyboardLayout = ParseCustomKeyboardLayout(document, CustomKeyboardLayout);
                m_builder.SetCustomKeyboardLayout(customKeyboardLayout);

                if (document.HasMember(CompassCameraOffset.c_str()))
                {
                    const rapidjson::Value& offsetJSON = document[CompassCameraOffset.c_str()];

                    Eegeo_ASSERT(offsetJSON.HasMember(Offset.c_str()));
                    float offset = offsetJSON[Offset.c_str()].GetDouble();
                    m_builder.SetCompassCameraOffset(offset);

                    Eegeo_ASSERT(offsetJSON.HasMember(OffsetTopDown.c_str()));
                    float offsetTopDown = offsetJSON[OffsetTopDown.c_str()].GetDouble();
                    m_builder.SetCompassCameraOffsetTopDown(offsetTopDown);
                }
                
                if (document.HasMember(CompassCameraDampingEnabled.c_str()) && !document[CompassCameraDampingEnabled.c_str()].IsNull())
                {
                    m_builder.SetCompassCameraDampingEnabled(document[CompassCameraDampingEnabled.c_str()].GetBool());
                }
                
                return m_builder.Build();
            }
            
            bool ApplicationConfigurationJsonParser::IsValidConfig(const std::string& serialized)
            {
                rapidjson::Document document;
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                return !hasParseError;
            }
            
            bool ApplicationConfigurationJsonParser::HasKey(const std::string& serialized, const std::string& key)
            {
                rapidjson::Document document;
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                if (!hasParseError) {
                    return document.HasMember(key.c_str());
                }
                return false;
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
                    
                    std::map<int, std::vector<std::string> > floorMapping;
                    for(rapidjson::SizeType j = 0; j < floorMappingArray.Size(); ++j)
                    {
                        floorMapping[floorMappingArray[j][BuildingFloorIndex.c_str()].GetInt()].push_back(floorMappingArray[j][TrackedFloorIndex.c_str()].GetString());
                    }
                    
                    SdkModel::ApplicationInteriorTrackingInfo interiorTrackingInfo(interiorId,
                                                                                   type,
                                                                                   interiorTrackingConfig,
                                                                                   floorMapping);
                    
                    interiorTrackingInfoList.insert(std::pair<std::string, SdkModel::ApplicationInteriorTrackingInfo>(interiorId.Value(),interiorTrackingInfo));
                }
            }

            void ApplicationConfigurationJsonParser::ParseFixedIndoorLocation(const rapidjson::Value& fixedIndoorLocation)
            {
                Eegeo_ASSERT(fixedIndoorLocation.HasMember(Latitude.c_str()),   "FixedIndoorLocation.Latitude not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember(Longitude.c_str()),  "FixedIndoorLocation.Longitude not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember(InteriorId.c_str()), "FixedIndoorLocation.InteriorId not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember(FloorIndex.c_str()), "FixedIndoorLocation.FloorIndex not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember(OrientationDegrees.c_str()), "FixedIndoorLocation.OrientationDegrees not found");
				m_builder.SetFixedIndoorLocation(Eegeo::Space::LatLong::FromDegrees(fixedIndoorLocation[Latitude.c_str()].GetDouble(), fixedIndoorLocation[Longitude.c_str()].GetDouble()),
                                                 fixedIndoorLocation[InteriorId.c_str()].GetString(),
										         fixedIndoorLocation[FloorIndex.c_str()].GetInt(),
										         fixedIndoorLocation[OrientationDegrees.c_str()].GetDouble());
            }

            Eegeo::Space::LatLongAltitude ApplicationConfigurationJsonParser::ParseLatLongAltitude(const rapidjson::Value& location)
            {
                Eegeo_ASSERT(location.HasMember(Latitude.c_str()),  "Latitude not found");
                Eegeo_ASSERT(location.HasMember(Longitude.c_str()), "Longitude not found");
                Eegeo_ASSERT(location.HasMember(Altitude.c_str()),  "Altitude not found");
                return Eegeo::Space::LatLongAltitude::FromDegrees(
                        location[Latitude.c_str()].GetDouble(),
                        location[Longitude.c_str()].GetDouble(),
                        location[Altitude.c_str()].GetDouble());
            }

            std::vector<Eegeo::Space::LatLongAltitude> ApplicationConfigurationJsonParser::ParseLatLongAltitudeArray(rapidjson::Value& pointsAst)
            {
                std::vector<Eegeo::Space::LatLongAltitude> points;
                for(rapidjson::SizeType i = 0; i < pointsAst.Size(); ++i)
                {
                    points.push_back(ParseLatLongAltitude(pointsAst[i]));
                }
                return points;
            }
        }
    }
}
