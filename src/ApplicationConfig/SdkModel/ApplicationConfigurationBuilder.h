// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationBuilder.h"
#include "Types.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationBuilder : public IApplicationConfigurationBuilder, private Eegeo::NonCopyable
            {
            private:
                std::string m_name;
                std::string m_eegeoApiKey;
                Eegeo::Space::LatLongAltitude m_interestLocation;
                float m_distanceToInterestMetres;
                float m_orientationDegrees;
                bool m_tryStartAtGpsLocation;
                std::string m_googleAnalyticsReferrerToken;
                std::string m_flurryAppKey;
                std::string m_yelpConsumerKey;
                std::string m_yelpConsumerSecret;
                std::string m_yelpOAuthToken;
                std::string m_yelpOAuthTokenSecret;
                std::string m_geoNamesUserName;
                std::string m_coverageTreeManifestURL;
                std::string m_themeManifestURL;
                std::string m_sqliteDbUrl;
                std::string m_searchServiceUrl;
                std::string m_myPinsWebServiceUrl;
                std::string m_myPinsWebServiceAuthToken;
                std::string m_productVersion;
                std::string m_buildNumber;
                std::string m_combinedVersionString;
                bool m_webProxyEnabled;
                std::string m_webProxyIpAddress;
                int m_webProxyPort;
                
                
            public:
                ApplicationConfigurationBuilder();
                
                IApplicationConfigurationBuilder& SetApplicationName(const std::string& name);
                
                IApplicationConfigurationBuilder& SetEegeoApiKey(const std::string& eegeoApiKey);
                
                IApplicationConfigurationBuilder& SetStartInterestPointLocation(const Eegeo::Space::LatLongAltitude& location);
                
                IApplicationConfigurationBuilder& SetStartDistanceFromInterestPoint(float distanceMetres);
                
                IApplicationConfigurationBuilder& SetStartOrientationAboutInterestPoint(float degrees);
                
                IApplicationConfigurationBuilder& SetTryStartAtGpsLocation(bool tryStartAtGpsLocation);
                
                IApplicationConfigurationBuilder& SetGoogleAnalyticsReferrerToken(const std::string& googleAnalyticsReferrerToken);
                
                IApplicationConfigurationBuilder& SetFlurryAppKey(const std::string& flurryAppKey);
                
                IApplicationConfigurationBuilder& SetYelpConsumerKey(const std::string& yelpConsumerKey);
                
                IApplicationConfigurationBuilder& SetYelpConsumerSecret(const std::string& yelpConsumerSecret);
                
                IApplicationConfigurationBuilder& SetYelpOAuthToken(const std::string& yelpOAuthToken);
                
                IApplicationConfigurationBuilder& SetYelpOAuthTokenSecret(const std::string& yelpOAuthTokenSecret);
                
                IApplicationConfigurationBuilder& SetGeoNamesUserName(const std::string& geoNamesUserName);
                
                IApplicationConfigurationBuilder& SetCoverageTreeManifestURL(const std::string& coverageTreeManifestUrl);
                
                IApplicationConfigurationBuilder& SetThemeManifestURL(const std::string& themesManifestUrl);
                
                IApplicationConfigurationBuilder& SetSqliteDbUrl(const std::string& SqliteDbUrl);
                
                IApplicationConfigurationBuilder& SetSearchServiceUrl(const std::string& searchServiceUrl);
                
                IApplicationConfigurationBuilder& SetMyPinsWebServiceUrl(const std::string& myPinsWebServiceUrl);
                
                IApplicationConfigurationBuilder& SetMyPinsWebServiceAuthToken(const std::string& myPinsWebServiceAuthToken);
                
                IApplicationConfigurationBuilder& SetProductVersion(const std::string& productVersion);
                
                IApplicationConfigurationBuilder& SetBuildNumber(const std::string& buildNumber);
                
                IApplicationConfigurationBuilder& SetCombinedVersionString(const std::string& combinedVersionString);
                
                IApplicationConfigurationBuilder& SetWebProxyEnabled(bool webProxyEnabled);
                
                IApplicationConfigurationBuilder& SetWebProxyIpAddress(const std::string& webProxyIpAddress);
                
                IApplicationConfigurationBuilder& SetWebProxyPort(int webProxyPort);
                
                ApplicationConfiguration Build();
            };
        }
    }
}
