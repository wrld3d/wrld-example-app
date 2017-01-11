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
                static const double DefaultAttractModePlaybackSpeed = 0.03;
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

                if (document.HasMember("Encrypted"))
                {
                    Eegeo_ASSERT(document.HasMember("HMAC_SHA1"), "must have HMAC_SHA1 digest field if Encrypted field is present");
                    
                    const std::string& encryptedValue = document["Encrypted"].GetString();
                    const std::string& digest = document["HMAC_SHA1"].GetString();

                    const std::string& decrypted = m_builder.Decrypt(encryptedValue);
                    const bool validHMAC = m_builder.ValidateHMAC(decrypted, digest);
                    Eegeo_ASSERT(validHMAC, "HMAC_SHA1 digest does not match, check that app secret matches that used to encrypt app config");

                    document.Parse<0>(decrypted.c_str());

                    Eegeo_ASSERT(!document.HasParseError(), "unable to parse Encrypted config field");
                }

                m_builder.SetProductVersion(m_defaultConfig.ProductVersion());
                m_builder.SetBuildNumber(m_defaultConfig.BuildNumber());

                Eegeo_ASSERT(document.HasMember("Name"));
                m_builder.SetApplicationName(document["Name"].GetString());

                Eegeo_ASSERT(document.HasMember("EegeoApiKey"));
                m_builder.SetEegeoApiKey(document["EegeoApiKey"].GetString());
                
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
                
                Eegeo_ASSERT(document.HasMember("GoogleAnalyticsReferrerToken"));
                m_builder.SetGoogleAnalyticsReferrerToken(document["GoogleAnalyticsReferrerToken"].GetString());
                
                Eegeo_ASSERT(document.HasMember("FlurryAppKey"), "FlurryAppKey config not found");
                m_builder.SetFlurryAppKey(document["FlurryAppKey"].GetString());
                
                Eegeo_ASSERT(document.HasMember("YelpConsumerKey"), "YelpConsumerKey config not found");
                m_builder.SetYelpConsumerKey(document["YelpConsumerKey"].GetString());
                
                Eegeo_ASSERT(document.HasMember("YelpConsumerSecret"), "YelpConsumerSecret config not found");
                m_builder.SetYelpConsumerSecret(document["YelpConsumerSecret"].GetString());
                
                Eegeo_ASSERT(document.HasMember("YelpOAuthToken"), "YelpOAuthToken config not found");
                m_builder.SetYelpOAuthToken(document["YelpOAuthToken"].GetString());
                
                Eegeo_ASSERT(document.HasMember("YelpOAuthTokenSecret"), "YelpOAuthTokenSecret config not found");
                m_builder.SetYelpOAuthTokenSecret(document["YelpOAuthTokenSecret"].GetString());
                
                Eegeo_ASSERT(document.HasMember("GeoNamesUserName"), "GeoNamesUserName config not found");
                m_builder.SetGeoNamesUserName(document["GeoNamesUserName"].GetString());
                
                Eegeo_ASSERT(document.HasMember("CoverageTreeManifestURL"), "CoverageTreeManifestURL config not found");
                m_builder.SetCoverageTreeManifestURL(document["CoverageTreeManifestURL"].GetString());
                
                Eegeo_ASSERT(document.HasMember("ThemeManifestURL"), "ThemeManifestURL config not found");
                m_builder.SetThemeManifestURL(document["ThemeManifestURL"].GetString());
                
                Eegeo_ASSERT(document.HasMember("SqliteDbUrl"), "SqliteDbUrl config not found");
                m_builder.SetSqliteDbUrl(document["SqliteDbUrl"].GetString());
                
                Eegeo_ASSERT(document.HasMember("EegeoSearchServiceUrl"), "EegeoSearchServiceUrl not found");
                m_builder.SetSearchServiceUrl(document["EegeoSearchServiceUrl"].GetString());
                
                Eegeo_ASSERT(document.HasMember("MyPinsWebServiceUrl"), "MyPinsWebServiceUrl config not found");
                m_builder.SetMyPinsWebServiceUrl(document["MyPinsWebServiceUrl"].GetString());
                
                Eegeo_ASSERT(document.HasMember("MyPinsWebServiceAuthToken"), "MyPinsWebServiceAuthToken config not found");
                m_builder.SetMyPinsWebServiceAuthToken(document["MyPinsWebServiceAuthToken"].GetString());
                
                Eegeo_ASSERT(document.HasMember("WebProxyEnabled"), "WebProxyEnabled config not found");
                m_builder.SetWebProxyEnabled(document["WebProxyEnabled"].GetBool());
                
                Eegeo_ASSERT(document.HasMember("WebProxyIpAddress"), "WebProxyIpAddress config not found");
                m_builder.SetWebProxyIpAddress(document["WebProxyIpAddress"].GetString());
                
                Eegeo_ASSERT(document.HasMember("WebProxyPort"), "WebProxyPort config not found");
                m_builder.SetWebProxyPort(document["WebProxyPort"].GetInt());

                if (document.HasMember("WebProxyIgnorePattern"))
                {
                    m_builder.SetWebProxyIgnorePattern(document["WebProxyIgnorePattern"].GetString());
                }
                
                std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*> restrictedBuildingModelArray;
                const char* wifiRestrictedBuildingTag = "WifiRestrictedBuildings";
                
                if (document.HasMember(wifiRestrictedBuildingTag))
                {
                    const rapidjson::Value& restrictedBuildingJsonArray = document[wifiRestrictedBuildingTag];
                    for (rapidjson::SizeType i = 0; i < restrictedBuildingJsonArray.Size(); i++)
                    {
                        const rapidjson::Value& restrictedBuilding = restrictedBuildingJsonArray[i];

                        Eegeo_ASSERT(restrictedBuilding.HasMember("InteriorId"), "InteriorId config not found");
                        std::string interiorId = restrictedBuilding["InteriorId"].GetString();

                        const rapidjson::Value& allowedWifiIDsJsonArray = restrictedBuilding["AllowedSSIDs"];
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

                if (document.HasMember("IsKioskTouchInputEnabled") && !document["IsKioskTouchInputEnabled"].IsNull())
                {
                    m_builder.SetIsKioskTouchInputEnabled(document["IsKioskTouchInputEnabled"].GetBool());
                }

                if (document.HasMember("IsInKioskMode") && !document["IsInKioskMode"].IsNull())
                {
					m_builder.SetIsInKioskMode(document["IsInKioskMode"].GetBool());
                }

                if (document.HasMember("StartAppInFullscreen") && !document["StartAppInFullscreen"].IsNull())
                {
                    m_builder.SetShouldStartFullscreen(document["StartAppInFullscreen"].GetBool());
                }

                Eegeo_ASSERT(document.HasMember("EmbeddedThemeTexturePath"), "EmbeddedThemeTexturePath not found");
                m_builder.SetEmbeddedThemeTexturePath(document["EmbeddedThemeTexturePath"].GetString());

                Eegeo_ASSERT(document.HasMember("TwitterAuthCode"), "TwitterAuthCode not found");
                m_builder.SetTwitterAuthCode(document["TwitterAuthCode"].GetString());

                if (document.HasMember("UseLabels") && !document["UseLabels"].IsNull())
                {
                    m_builder.SetUseLabels(document["UseLabels"].GetBool());
                }

                std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;
                if(document.HasMember("IndoorTrackedBuildings") && !document["IndoorTrackedBuildings"].IsNull())
                {
                    const rapidjson::Value& indoorTrackedBuildingsArray = document["IndoorTrackedBuildings"];
                    ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
                    m_builder.SetInteriorTrackingInfo(interiorTrackingInfoList);
                }

                m_builder.SetAttractModeTimeoutMs(document.HasMember("AttractModeTimeout") ? document["AttractModeTimeout"].GetInt() : 0);
                if(document.HasMember("AttractModeTargetSpline"))
                {
                    m_builder.SetAttractModeTargetSplinePoints(ParseLatLongAltitudeArray(document["AttractModeTargetSpline"]));
                }

                if(document.HasMember("AttractModePositionSpline"))
                {
                    m_builder.SetAttractModePositionSplinePoints(ParseLatLongAltitudeArray(document["AttractModePositionSpline"]));
                }

                m_builder.SetAttractModePlaybackSpeed(document.HasMember("AttractModePlaybackSpeed")
                    ? document["AttractModePlaybackSpeed"].GetDouble()
                    : DefaultAttractModePlaybackSpeed);

                if(document.HasMember("FixedIndoorLocation"))
                {
                    ParseFixedIndoorLocation(document["FixedIndoorLocation"]);
                }
                
                return m_builder.Build();
            }

			void ApplicationConfigurationJsonParser::ParseIndoorTrackingInfo(std::map<std::string,
                                                                             SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                                                             const rapidjson::Value& indoorTrackedBuildingsArray)
            {
                for(rapidjson::SizeType i = 0; i < indoorTrackedBuildingsArray.Size(); ++i)
                {
                    const rapidjson::Value& building = indoorTrackedBuildingsArray[i];
                    
                    Eegeo_ASSERT(building.HasMember("InteriorId"), "Interior Id not found");
                    const std::string& id = building["InteriorId"].GetString();
                    const Eegeo::Resources::Interiors::InteriorId& interiorId(id);
                    
                    Eegeo_ASSERT(building.HasMember("Type"), "Type not found");
                    const std::string& type = building["Type"].GetString();

                    
                    Eegeo_ASSERT(building.HasMember("Config"), "Config not found");
                    const std::string& apiKey = building["Config"][0]["ApiKey"].GetString();
                    const std::string& apiSecret = building["Config"][0]["ApiSecret"].GetString();
                    SdkModel::ApplicationInteriorTrackingConfig interiorTrackingConfig(apiKey, apiSecret);
                    
                    Eegeo_ASSERT(building.HasMember("FloorMapping"), "FloorMapping not found");
                    const rapidjson::Value& floorMappingArray = building["FloorMapping"];
                    
                    std::map<int, std::string> floorMapping;
                    for(rapidjson::SizeType j = 0; j < floorMappingArray.Size(); ++j)
                    {
                        floorMapping[floorMappingArray[j]["BuildingFloorIndex"].GetInt()] = floorMappingArray[j]["TrackedFloorIndex"].GetString();
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
                Eegeo_ASSERT(fixedIndoorLocation.HasMember("Latitude"),   "FixedIndoorLocation.Latitude not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember("Longitude"),  "FixedIndoorLocation.Longitude not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember("InteriorId"), "FixedIndoorLocation.InteriorId not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember("FloorIndex"), "FixedIndoorLocation.FloorIndex not found");
                Eegeo_ASSERT(fixedIndoorLocation.HasMember("OrientationDegrees"), "FixedIndoorLocation.OrientationDegrees not found");
				m_builder.SetFixedIndoorLocation(Eegeo::Space::LatLong::FromDegrees(fixedIndoorLocation["Latitude"].GetDouble(), fixedIndoorLocation["Longitude"].GetDouble()),
                                                 fixedIndoorLocation["InteriorId"].GetString(),
										         fixedIndoorLocation["FloorIndex"].GetInt(),
										         fixedIndoorLocation["OrientationDegrees"].GetDouble());
            }

            Eegeo::Space::LatLongAltitude ApplicationConfigurationJsonParser::ParseLatLongAltitude(const rapidjson::Value& location)
            {
                Eegeo_ASSERT(location.HasMember("Latitude"),  "Latitude not found");
                Eegeo_ASSERT(location.HasMember("Longitude"), "Longitude not found");
                Eegeo_ASSERT(location.HasMember("Altitude"),  "Altitude not found");
                return Eegeo::Space::LatLongAltitude::FromDegrees(
                        location["Latitude"].GetDouble(),
                        location["Longitude"].GetDouble(),
                        location["Altitude"].GetDouble());
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
