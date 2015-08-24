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
                
                ApplicationConfiguration Build();
            };
        }
    }
}
