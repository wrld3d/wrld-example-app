// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(const std::string& name,
                                                           const Eegeo::Space::LatLongAltitude& interestLocation,
                                                           float distanceToInterestMetres,
                                                           float orientationDegrees,
                                                           bool tryStartAtGpsLocation,
                                                           const std::string& googleAnalyticsReferrerToken,
                                                           const std::string& productVersion,
                                                           const std::string& buildNumber,
                                                           const std::string& combinedVersionString,
                                                           const std::string& coverageTreeManifestURL,
                                                           const std::string& themeManifestURL)
        : m_name(name)
        , m_interestLocation(interestLocation)
        , m_distanceToInterestMetres(distanceToInterestMetres)
        , m_orientationDegrees(orientationDegrees)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        {
        }
        
        const std::string& ApplicationConfiguration::Name() const
        {
            return m_name;
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

        const std::string& ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }

        const std::string& ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }
    }
}
