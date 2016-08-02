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
                
                Eegeo_ASSERT(document.HasMember("SearchServiceUrl"), "SearchServiceUrl not found");
                m_builder.SetSearchServiceUrl(document["SearchServiceUrl"].GetString());
                
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
                
                Eegeo_ASSERT(document.HasMember("Buildings"), "Buildings config not found");
                // Using a reference for consecutive access is handy and faster.
                const rapidjson::Value& buildingArray = document["Buildings"];
                std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*> buildingInfoList;
                for (rapidjson::SizeType i = 0; i < buildingArray.Size(); i++) // Uses SizeType instead of size_t
                {
                    const rapidjson::Value& building = buildingArray[i];
                    Eegeo_ASSERT(building.HasMember("SenionMapKey"), "SenionMapKey config not found");
                    std::string mapKey = building["SenionMapKey"].GetString();
                    Eegeo_ASSERT(building.HasMember("SenionMapCustomerID"), "SenionMapCustomerID config not found");
                    std::string customerID = building["SenionMapCustomerID"].GetString();
                    Eegeo_ASSERT(building.HasMember("interior_id"), "interior_id config not found");
                    std::string interiorID = building["interior_id"].GetString();
                    
                    Eegeo_ASSERT(building.HasMember("SenionidToFloorIndexMapping"), "Senion to local floor index config not found");
                    std::map<int,int> senionFloorMapping;
                    const rapidjson::Value& floorMappingArray = building["SenionidToFloorIndexMapping"];
                    for (rapidjson::SizeType y = 0; y < floorMappingArray.Size(); y++)
                    {
                        const rapidjson::Value& senionMapping = floorMappingArray[y];

                        Eegeo_ASSERT(senionMapping.HasMember("SenionIndex"), "Senion index config not found");
                        Eegeo_ASSERT(senionMapping.HasMember("FloorIindex"), "Floor index config not found");
                        
                        senionFloorMapping[static_cast<float>(senionMapping["SenionIndex"].GetInt())] = static_cast<float>(senionMapping["FloorIindex"].GetInt());
                    }
                    
                    ExampleApp::ApplicationConfig::ApplicationBuildingInfo * buildingInfo = Eegeo_NEW(ExampleApp::ApplicationConfig::ApplicationBuildingInfo)(mapKey, customerID, interiorID, senionFloorMapping);
                    buildingInfoList.push_back(buildingInfo);
                }
                m_builder.SetBuildingInfoArray(buildingInfoList);
                
                return m_builder.Build();
            }
        }
    }
}
