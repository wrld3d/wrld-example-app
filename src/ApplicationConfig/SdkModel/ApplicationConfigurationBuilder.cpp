// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationBuilder.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationBuilder::ApplicationConfigurationBuilder()
            : m_name("")
            , m_eegeoApiKey("")
            , m_interestLocation(0.0, 0.0, 0.0)
            , m_distanceToInterestMetres(0.f)
            , m_orientationDegrees(0.f)
            , m_tryStartAtGpsLocation(false)
            , m_googleAnalyticsReferrerToken("")
            , m_flurryAppKey("")
            , m_yelpConsumerKey("")
            , m_yelpConsumerSecret("")
            , m_yelpOAuthToken("")
            , m_yelpOAuthTokenSecret("")
            , m_geoNamesUserName("")
            , m_coverageTreeManifestURL("")
            , m_themeManifestURL("")
            {
                
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetApplicationName(const std::string& name)
            {
                m_name = name;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetEegeoApiKey(const std::string& eegeoApiKey)
            {
                m_eegeoApiKey = eegeoApiKey;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetStartInterestPointLocation(const Eegeo::Space::LatLongAltitude& location)
            {
                m_interestLocation = location;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetStartDistanceFromInterestPoint(float distanceMetres)
            {
                m_distanceToInterestMetres = distanceMetres;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetStartOrientationAboutInterestPoint(float degrees)
            {
                m_orientationDegrees = degrees;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetTryStartAtGpsLocation(bool tryStartAtGpsLocation)
            {
                m_tryStartAtGpsLocation = tryStartAtGpsLocation;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetGoogleAnalyticsReferrerToken(const std::string& googleAnalyticsReferrerToken)
            {
                m_googleAnalyticsReferrerToken = googleAnalyticsReferrerToken;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetFlurryAppKey(const std::string& flurryAppKey)
            {
                m_flurryAppKey = flurryAppKey;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetYelpConsumerKey(const std::string& yelpConsumerKey)
            {
                m_yelpConsumerKey = yelpConsumerKey;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetYelpConsumerSecret(const std::string& yelpConsumerSecret)
            {
                m_yelpConsumerSecret = yelpConsumerSecret;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetYelpOAuthToken(const std::string& yelpOAuthToken)
            {
                m_yelpOAuthToken = yelpOAuthToken;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetYelpOAuthTokenSecret(const std::string& yelpOAuthTokenSecret)
            {
                m_yelpOAuthTokenSecret = yelpOAuthTokenSecret;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetGeoNamesUserName(const std::string& geoNamesUserName)
            {
                m_geoNamesUserName = geoNamesUserName;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetCoverageTreeManifestURL(const std::string& coverageTreeManifestURL)
            {
                m_coverageTreeManifestURL = coverageTreeManifestURL;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetThemeManifestURL(const std::string& themeManifestURL)
            {
                m_themeManifestURL = themeManifestURL;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetSqliteDbUrl(const std::string& SqliteDbUrl)
            {
                m_sqliteDbUrl = SqliteDbUrl;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetProductVersion(const std::string& productVersion)
            {
                m_productVersion = productVersion;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetBuildNumber(const std::string& buildNumber)
            {
                m_buildNumber = buildNumber;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetCombinedVersionString(const std::string& combinedVersionString)
            {
                m_combinedVersionString = combinedVersionString;
                return *this;
            }
            
            ApplicationConfiguration ApplicationConfigurationBuilder::Build()
            {
                return ApplicationConfiguration(m_name,
                                                m_eegeoApiKey,
                                                m_interestLocation,
                                                m_distanceToInterestMetres,
                                                m_orientationDegrees,
                                                m_tryStartAtGpsLocation,
                                                m_googleAnalyticsReferrerToken,
                                                m_flurryAppKey,
                                                m_yelpConsumerKey,
                                                m_yelpConsumerSecret,
                                                m_yelpOAuthToken,
                                                m_yelpOAuthTokenSecret,
                                                m_geoNamesUserName,
                                                m_coverageTreeManifestURL,
                                                m_themeManifestURL,
                                                m_sqliteDbUrl,
                                                m_productVersion,
                                                m_buildNumber,
                                                m_combinedVersionString);
            }
        }
    }
}
