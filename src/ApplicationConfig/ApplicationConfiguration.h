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
            std::string m_buildVersion;
            
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
                                     const std::string& buildVersion);
            
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

            const std::string& BuildVersion() const;
        };
    }
}
