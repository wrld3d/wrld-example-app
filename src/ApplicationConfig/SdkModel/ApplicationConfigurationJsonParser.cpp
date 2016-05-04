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
                return m_builder.Build();
            }
        }
    }
}
