// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(const std::string& name,
                                                           const std::string& eegeoApiKey,
                                                           const Eegeo::Space::LatLongAltitude& interestLocation,
                                                           float distanceToInterestMetres,
                                                           float orientationDegrees,
                                                           bool tryStartAtGpsLocation,
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
                                                           const std::string& searchServiceUrl,
                                                           const std::string& myPinsWebServiceUrl,
                                                           const std::string& myPinsWebServiceAuthToken,
                                                           const std::string& productVersion,
                                                           const std::string& buildNumber,
                                                           const std::string& combinedVersionString)
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_interestLocation(interestLocation)
        , m_distanceToInterestMetres(distanceToInterestMetres)
        , m_orientationDegrees(orientationDegrees)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
        , m_flurryAppKey(flurryAppKey)
        , m_yelpConsumerKey(yelpConsumerKey)
        , m_yelpConsumerSecret(yelpConsumerSecret)
        , m_yelpOAuthToken(yelpOAuthToken)
        , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
        , m_geoNamesUserName(geoNamesUserName)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        , m_sqliteDbUrl(sqliteDbUrl)
        , m_searchServiceUrl(searchServiceUrl)
        , m_myPinsWebServiceUrl(myPinsWebServiceUrl)
        , m_myPinsWebServiceAuthToken(myPinsWebServiceAuthToken)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        {
            
        }
        
        const std::string& ApplicationConfiguration::Name() const
        {
            return m_name;
        }
        
        const std::string& ApplicationConfiguration::EegeoApiKey() const
        {
            return m_eegeoApiKey;
        }
        
        const Eegeo::Space::LatLongAltitude& ApplicationConfiguration::InterestLocation() const
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
        
        const std::string& ApplicationConfiguration::GoogleAnalyticsReferrerToken() const
        {
            return m_googleAnalyticsReferrerToken;
        }
        
        const std::string& ApplicationConfiguration::FlurryAppKey() const
        {
            return m_flurryAppKey;
        }
        
        const std::string& ApplicationConfiguration::YelpConsumerKey() const
        {
            return m_yelpConsumerKey;
        }
        
        const std::string& ApplicationConfiguration::YelpConsumerSecret() const
        {
            return m_yelpConsumerSecret;
        }
        
        const std::string& ApplicationConfiguration::YelpOAuthToken() const
        {
            return m_yelpOAuthToken;
        }
        
        const std::string& ApplicationConfiguration::YelpOAuthTokenSecret() const
        {
            return m_yelpOAuthTokenSecret;
        }
        
        const std::string& ApplicationConfiguration::GeoNamesUserName() const
        {
            return m_geoNamesUserName;
        }
        
        const std::string& ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }
        
        const std::string& ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }
        
        const std::string& ApplicationConfiguration::SqliteDbUrl() const
        {
            return m_sqliteDbUrl;
        }
        
        const std::string& ApplicationConfiguration::SearchServiceUrl() const
        {
            return m_searchServiceUrl;
        }

        const std::string& ApplicationConfiguration::MyPinsWebServiceUrl() const
        {
            return m_myPinsWebServiceUrl;
        }
        
        const std::string& ApplicationConfiguration::MyPinsWebServiceAuthToken() const
        {
            return m_myPinsWebServiceAuthToken;
        }

        const std::string& ApplicationConfiguration::ProductVersion() const
        {
            return m_productVersion;
        }
        
        const std::string& ApplicationConfiguration::BuildNumber() const
        {
            return m_buildNumber;
        }
        
        const std::string& ApplicationConfiguration::CombinedVersionString() const
        {
            return m_combinedVersionString;
        }
    }
}
