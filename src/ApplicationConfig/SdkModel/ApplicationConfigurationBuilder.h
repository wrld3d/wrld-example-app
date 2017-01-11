// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationBuilder.h"
#include "Types.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationBuilder : public IApplicationConfigurationBuilder, private Eegeo::NonCopyable
            {
            private:
                const IApplicationConfigurationCipher& m_cipher;
                const std::string m_configKey;

                std::string m_name;
                std::string m_eegeoApiKey;
                Eegeo::Space::LatLongAltitude m_interestLocation;
                float m_distanceToInterestMetres;
                float m_orientationDegrees;
                bool m_tryStartAtGpsLocation;
                bool m_shouldStartFullscreen;
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
                std::string m_eegeoSearchServiceUrl;
                std::string m_myPinsWebServiceUrl;
                std::string m_myPinsWebServiceAuthToken;
                std::string m_productVersion;
                std::string m_buildNumber;
                std::string m_combinedVersionString;
                bool m_webProxyEnabled;
                std::string m_webProxyIpAddress;
                int m_webProxyPort;
                std::string m_webProxyIgnorePattern;
                std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>m_buildingsInfo;
                std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>m_restrictedBuildingsInfo;
                bool m_isKioskTouchInputEnabled;
				bool m_isInKioskMode;

                std::string m_embeddedThemeTexturePath;
                std::string m_twitterAuthCode;
                bool m_useLabels;
                bool m_useJapaneseFonts;

                Eegeo::Space::LatLong m_fixedLatlong;
                std::string m_fixedInteriorId;
                int m_fixedFloorIndex;
                double m_fixedHeadingDegrees;

                std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> m_interiorTrackingInfo;

                std::vector<Eegeo::Space::LatLongAltitude> m_attractModeTargetSplinePoints;
                std::vector<Eegeo::Space::LatLongAltitude> m_attractModePositionSplinePoints;

                long long m_attractModeTimeoutMs;
                double m_attractModePlaybackSpeed;
                
            public:
                ApplicationConfigurationBuilder(const IApplicationConfigurationCipher& applicationConfigurationEncryption,
                                                const std::string& configKey);
                
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
                
                IApplicationConfigurationBuilder& SetSearchServiceUrl(const std::string& eegeoSearchServiceUrl);
                
                IApplicationConfigurationBuilder& SetMyPinsWebServiceUrl(const std::string& myPinsWebServiceUrl);
                
                IApplicationConfigurationBuilder& SetMyPinsWebServiceAuthToken(const std::string& myPinsWebServiceAuthToken);
                
                IApplicationConfigurationBuilder& SetProductVersion(const std::string& productVersion);
                
                IApplicationConfigurationBuilder& SetBuildNumber(const std::string& buildNumber);
                
                IApplicationConfigurationBuilder& SetCombinedVersionString(const std::string& combinedVersionString);
                
                IApplicationConfigurationBuilder& SetWebProxyEnabled(bool webProxyEnabled);
                
                IApplicationConfigurationBuilder& SetWebProxyIpAddress(const std::string& webProxyIpAddress);
                
                IApplicationConfigurationBuilder& SetWebProxyPort(int webProxyPort);

                IApplicationConfigurationBuilder& SetWebProxyIgnorePattern(const std::string& webProxyIgnorePattern);
                
                IApplicationConfigurationBuilder& SetBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&infoBuildingList);

                IApplicationConfigurationBuilder& SetRestrictedBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingInfo);
                
                IApplicationConfigurationBuilder& SetShouldStartFullscreen(bool startFullscreen);
                
                IApplicationConfigurationBuilder& SetIsKioskTouchInputEnabled(bool kioskTouchInputEnabled);

				IApplicationConfigurationBuilder& SetIsInKioskMode(bool isInKioskMode);

                IApplicationConfigurationBuilder& SetEmbeddedThemeTexturePath(const std::string& embeddedThemeTexturePath);

                IApplicationConfigurationBuilder& SetTwitterAuthCode(const std::string& twitterAuthCode);

                IApplicationConfigurationBuilder& SetUseLabels(bool useLabels);

                IApplicationConfigurationBuilder& SetInteriorTrackingInfo(const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo);

                IApplicationConfigurationBuilder& SetFixedIndoorLocation(const Eegeo::Space::LatLong latlong, const std::string& interiorId, const int floorIndex, const double headingDegrees);

                IApplicationConfigurationBuilder& SetAttractModeTargetSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points);
                IApplicationConfigurationBuilder& SetAttractModePositionSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points);
                IApplicationConfigurationBuilder& SetAttractModeTimeoutMs(const long long timeoutMs);
                IApplicationConfigurationBuilder& SetAttractModePlaybackSpeed(const double playbackSpeed);
                
                std::string Decrypt(const std::string& message) const;

                bool ValidateHMAC(const std::string& message, const std::string& hmac) const;
                
                ApplicationConfiguration Build();
            };
        }
    }
}
