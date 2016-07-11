// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(
            const std::string& name,
            const std::string& eegeoApiKey,
            const std::string& productVersion,
            const std::string& buildNumber,
            const std::string& combinedVersionString,
            const std::string& coverageTreeManifestURL,
            const std::string& themeManifestURL,
            const std::string& embeddedThemeTexturePath,
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
            const std::string& eegeoSearchServiceUrl,
            const std::string& myPinsWebServiceUrl,
            const std::string& myPinsWebServiceAuthToken,
            const std::string& twitterAuthCode,
            const bool isKioskTouchInputEnabled
            )
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        , m_embeddedThemeTexturePath(embeddedThemeTexturePath)
        , m_interestLocation(interestLocation)
        , m_distanceToInterestMetres(distanceToInterestMetres)
        , m_orientationDegrees(orientationDegrees)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_shouldStartFullscreen(startFullscreen)
        , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
        , m_flurryAppKey(flurryAppKey)
        , m_yelpConsumerKey(yelpConsumerKey)
        , m_yelpConsumerSecret(yelpConsumerSecret)
        , m_yelpOAuthToken(yelpOAuthToken)
        , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
        , m_geoNamesUserName(geoNamesUserName)
        , m_eegeoSearchServiceUrl(eegeoSearchServiceUrl)
        , m_myPinsWebServiceUrl(myPinsWebServiceUrl)
        , m_myPinsWebServiceAuthToken(myPinsWebServiceAuthToken)
        , m_twitterAuthCode(twitterAuthCode)
        , m_isKioskTouchInputEnabled(isKioskTouchInputEnabled)
        {
        }
        
        std::string ApplicationConfiguration::Name() const
        {
            return m_name;
        }

        std::string ApplicationConfiguration::EegeoApiKey() const
        {
            return m_eegeoApiKey;
        }

        std::string ApplicationConfiguration::ProductVersion() const
        {
            return m_productVersion;
        }

        std::string ApplicationConfiguration::BuildNumber() const
        {
            return m_buildNumber;
        }

        std::string ApplicationConfiguration::CombinedVersionString() const
        {
            return m_combinedVersionString;
        }

        std::string ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }

        std::string ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }

        std::string ApplicationConfiguration::EmbeddedThemeTexturePath() const
        {
            return m_embeddedThemeTexturePath;
        }

        Eegeo::Space::LatLongAltitude ApplicationConfiguration::InterestLocation() const
        {
            return m_interestLocation;
        }
        
        float ApplicationConfiguration::DistanceToInterestMetres() const
        {
            return m_distanceToInterestMetres;
        }
        
        float ApplicationConfiguration::OrientationDegrees() const
        {
            return m_orientationDegrees;
        }
        
        bool ApplicationConfiguration::TryStartAtGpsLocation() const
        {
            return m_tryStartAtGpsLocation;
        }
        
        std::string ApplicationConfiguration::GoogleAnalyticsReferrerToken() const
        {
            return m_googleAnalyticsReferrerToken;
        }

        std::string ApplicationConfiguration::FlurryAppKey() const
        {
            return m_flurryAppKey;
        }

        std::string ApplicationConfiguration::YelpConsumerKey() const
        {
            return m_yelpConsumerKey;
        }

        std::string ApplicationConfiguration::YelpConsumerSecret() const
        {
            return m_yelpConsumerSecret;
        }

        std::string ApplicationConfiguration::YelpOAuthToken() const
        {
            return m_yelpOAuthToken;
        }

        std::string ApplicationConfiguration::YelpOAuthTokenSecret() const
        {
            return m_yelpOAuthTokenSecret;
        }

        std::string ApplicationConfiguration::GeoNamesUserName() const
        {
            return m_geoNamesUserName;
        }

        std::string ApplicationConfiguration::EegeoSearchServiceUrl() const
        {
            return m_eegeoSearchServiceUrl;
        }

        std::string ApplicationConfiguration::MyPinsWebServiceUrl() const
        {
            return m_myPinsWebServiceUrl;
        }

        std::string ApplicationConfiguration::MyPinsWebServiceAuthToken() const
        {
            return m_myPinsWebServiceAuthToken;
        }

        std::string ApplicationConfiguration::TwitterAuthCode() const
        {
            return m_twitterAuthCode;
        }

        bool ApplicationConfiguration::IsKioskTouchInputEnabled() const
        {
            return m_isKioskTouchInputEnabled;
        }

        bool ApplicationConfiguration::ShouldStartFullscreen() const
        {
            return m_shouldStartFullscreen;
        }
    }
}
