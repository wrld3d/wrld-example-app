// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "ApplicationBuildingInfo.h"
#include "RestrictedBuildingInfo.h"
#include <vector>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration
        {
        private:
            std::string m_name;
            std::string m_productVersion;
            std::string m_buildNumber;
            std::string m_combinedVersionString;
            std::string m_coverageTreeManifestURL;
            std::string m_themeManifestURL;
            std::string m_embeddedThemeTexturePath;

            std::string m_eegeoApiKey;
            Eegeo::Space::LatLongAltitude m_interestLocation;
            float m_distanceToInterestMetres;
            float m_orientationDegrees;
            bool m_tryStartAtGpsLocation;
            bool m_shouldStartFullscreen;
            std::string m_flurryAppKey;
            std::string m_yelpConsumerKey;
            std::string m_yelpConsumerSecret;
            std::string m_yelpOAuthToken;
            std::string m_yelpOAuthTokenSecret;
            std::string m_geoNamesUserName;
            std::string m_twitterAuthCode;
            std::string m_googleAnalyticsReferrerToken;
            std::string m_sqliteDbUrl;
            std::string m_eegeoSearchServiceUrl;
            std::string m_myPinsWebServiceUrl;
            std::string m_myPinsWebServiceAuthToken;
            bool m_webProxyEnabled;
            std::string m_webProxyIpAddress;
            int m_webProxyPort;
            std::string m_webProxyIgnorePattern;
            std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>m_buildingsInfo;
            std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>m_restrictedBuildingsInfo;
            bool m_isKioskTouchInputEnabled;
            bool m_useLabels;
            
            std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> m_interiorTrackingInfo;

        public:
            
            ApplicationConfiguration(const std::string& name,
                                     const std::string& eegeoApiKey,
                                     const Eegeo::Space::LatLongAltitude& interestLocation,
                                     float distanceToInterestMetres,
                                     float orientationDegrees,
                                     bool tryStartAtGpsLocation,
                                     bool startFullscreen,
                                     const std::string& googleAnalyticsReferrerToken,
                                     const std::string& flurryAppKey,
                                     const std::string& yelpConsumerKey,
                                     const std::string& yelpConsumerSecret,
                                     const std::string& yelpOAuthToken,
                                     const std::string& yelpOAuthTokenSecret,
                                     const std::string& geoNamesUserName,
                                     const std::string& coverageTreeManifestURL,
                                     const std::string& themeManifestURL,
                                     const std::string& sqliteDbUrl,
                                     const std::string& eegeoSearchServiceUrl,
                                     const std::string& myPinsWebServiceUrl,
                                     const std::string& myPinsWebServiceAuthToken,
                                     const std::string& productVersion,
                                     const std::string& buildNumber,
                                     const std::string& combinedVersionString,
                                     bool webProxyEnabled,
                                     const std::string& webProxyIpAddress,
                                     int webProxyPort,
                                     const std::string& webProxyIgnorePattern,
                                     const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&buildingsInfo,
                                     const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingsInfo,
                                     const bool isKioskTouchInputEnabled,
					                 const std::string& embeddedThemeTexturePath,
					                 const std::string& twitterAuthCode,
					                 bool m_useLabels,
					                 const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo);
            
            std::string Name() const;

            std::string EegeoApiKey() const;

            std::string EmbeddedThemeTexturePath() const;
            
            const Eegeo::Space::LatLongAltitude& InterestLocation() const;
            
            float DistanceToInterestMetres() const;
            
            float OrientationDegrees() const;
            
            bool TryStartAtGpsLocation() const;

            bool ShouldStartFullscreen() const;
            
            std::string GoogleAnalyticsReferrerToken() const;

            std::string TwitterAuthCode() const;
            
            bool UseLabels() const;
            std::string FlurryAppKey() const;
            
            std::string YelpConsumerKey() const;
            
            std::string YelpConsumerSecret() const;
            
            std::string YelpOAuthToken() const;
            
            std::string YelpOAuthTokenSecret() const;
            
            std::string GeoNamesUserName() const;
            
            std::string CoverageTreeManifestURL() const;
            
            std::string ThemeManifestURL() const;
            
            std::string SqliteDbUrl() const;
            
            std::string EegeoSearchServiceUrl() const;
            
            std::string MyPinsWebServiceUrl() const;
            
            std::string MyPinsWebServiceAuthToken() const;
            
            std::string ProductVersion() const;
            
            const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& InteriorTrackingInfo() const;
            std::string BuildNumber() const;
            
            std::string CombinedVersionString() const;
            
            bool WebProxyEnabled() const;
            
            std::string WebProxyIpAddress() const;
            
            int WebProxyPort() const;
            
            std::string WebProxyIgnorePattern() const;
            
            const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>& BuildingsInfo() const;
            
            const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>& RestrictedBuildingsInfo() const;
            
            bool IsKioskTouchInputEnabled() const;
        };
    }
}
