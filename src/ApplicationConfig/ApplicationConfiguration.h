// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration
        {
        private:
            std::string m_name;
            const std::string m_eegeoApiKey;
            Eegeo::Space::LatLongAltitude m_interestLocation;
            float m_distanceToInterestMetres;
            float m_orientationDegrees;
            bool m_tryStartAtGpsLocation;
            const std::string m_googleAnalyticsReferrerToken;
            const std::string m_flurryAppKey;
            const std::string m_yelpConsumerKey;
            const std::string m_yelpConsumerSecret;
            const std::string m_yelpOAuthToken;
            const std::string m_yelpOAuthTokenSecret;
            const std::string m_geoNamesUserName;
            const std::string m_coverageTreeManifestURL;
            const std::string m_themeManifestURL;
            const std::string m_sqliteDbUrl;
            const std::string m_searchServiceUrl;
            const std::string m_myPinsWebServiceUrl;
            const std::string m_myPinsWebServiceAuthToken;
            const std::string m_productVersion;
            const std::string m_buildNumber;
            const std::string m_combinedVersionString;
            bool m_webProxyEnabled;
            const std::string m_webProxyIpAddress;
            int m_webProxyPort;
            
        public:
            
            ApplicationConfiguration(const std::string& name,
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
                                     const std::string& combinedVersionString,
                                     bool webProxyEnabled,
                                     const std::string& webProxyIpAddress,
                                     int webProxyPort);
            
            const std::string& Name() const;
            
            const std::string& EegeoApiKey() const;
            
            const Eegeo::Space::LatLongAltitude& InterestLocation() const;
            
            float DistanceToInterestMetres() const;
            
            float OrientationDegrees() const;
            
            bool TryStartAtGpsLocation() const;
            
            const std::string& GoogleAnalyticsReferrerToken() const;
            
            const std::string& FlurryAppKey() const;
            
            const std::string& YelpConsumerKey() const;
            
            const std::string& YelpConsumerSecret() const;
            
            const std::string& YelpOAuthToken() const;
            
            const std::string& YelpOAuthTokenSecret() const;
            
            const std::string& GeoNamesUserName() const;
            
            const std::string& CoverageTreeManifestURL() const;
            
            const std::string& ThemeManifestURL() const;
            
            const std::string& SqliteDbUrl() const;
            
            const std::string& SearchServiceUrl() const;
            
            const std::string& MyPinsWebServiceUrl() const;
            
            const std::string& MyPinsWebServiceAuthToken() const;
			
            const std::string& ProductVersion() const;
            
            const std::string& BuildNumber() const;
            
            const std::string& CombinedVersionString() const;
            
            bool WebProxyEnabled() const;
            
            const std::string& WebProxyIpAddress() const;
            
            int WebProxyPort() const;
            
        };
    }
}
