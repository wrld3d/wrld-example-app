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
            const std::string& indoorId,
            const int floorIndex,
            bool tryStartAtGpsLocation,
            bool startFullscreen,
            bool performStartUpSearch,
            const std::string& startUpSearchTag,
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
            const std::string& myPinsPoiSetId,
            const bool isKioskTouchInputEnabled,
            const bool isInKioskMode,
            const bool useJapaneseFont,
            const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo,
            const SdkModel::ApplicationFixedIndoorLocation& fixedIndoorLocation,
            const std::vector<Eegeo::Space::LatLongAltitude>& attractModeTargetSplinePoints,
            const std::vector<Eegeo::Space::LatLongAltitude>& attractModePositionSplinePoints,
            const long long attractModeTimeoutMs,
            const float attractModePlaybackSpeed,
            const std::string& optionsAdminPassword,
            const long long& surveyRequirementTimeSec,
            const std::string& timerSurveyUrl,
            const std::string& hockeyAppId,
            bool hasMapScene,
            const std::string& mapSceneId,
			const std::vector<std::vector<std::string>>& customKeyboardLayout,
            const std::vector<SdkModel::ApplicationMenuItemTagSearchConfig>& outdoorSearchMenuItems,
            bool overrideIndoorSearchMenuItems
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
        , m_indoorId(indoorId)
        , m_floorIndex(floorIndex)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_shouldStartFullscreen(startFullscreen)
        , m_shouldPerformStartUpSearch(performStartUpSearch)
        , m_startUpSearchTag(startUpSearchTag)
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
        , m_myPinsPoiSetId(myPinsPoiSetId)
        , m_isKioskTouchInputEnabled(isKioskTouchInputEnabled)
        , m_isInKioskMode(isInKioskMode)
        , m_useJapaneseFont(useJapaneseFont)
        , m_interiorTrackingInfo(interiorTrackingInfo)
        , m_fixedIndoorLocation(fixedIndoorLocation)
        , m_attractModeTargetSplinePoints(attractModeTargetSplinePoints)
        , m_attractModePositionSplinePoints(attractModePositionSplinePoints)
        , m_attractModeTimeoutMs(attractModeTimeoutMs)
        , m_attractModePlaybackSpeed(attractModePlaybackSpeed)
        , m_optionsAdminPassword(optionsAdminPassword)
        , m_surveyRequirementTimeSec(surveyRequirementTimeSec)
        , m_timerSurveyUrl(timerSurveyUrl)
        , m_hockeyAppId(hockeyAppId)
        , m_hasMapScene(hasMapScene)
        , m_mapSceneId(mapSceneId)
		, m_customKeyboardLayout(customKeyboardLayout)
        , m_outdoorSearchMenuItems(outdoorSearchMenuItems)
        , m_overrideIndoorSearchMenuItems(overrideIndoorSearchMenuItems)
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
        
        std::string ApplicationConfiguration::IndoorId() const
        {
            return m_indoorId;
        }
        
        int ApplicationConfiguration::FloorIndex() const
        {
            return m_floorIndex;
        }
        
        bool ApplicationConfiguration::TryStartAtGpsLocation() const
        {
            return m_tryStartAtGpsLocation;
        }
        
        bool ApplicationConfiguration::ShouldPerformStartUpSearch() const
        {
            return m_shouldPerformStartUpSearch;
        }
        
        std::string ApplicationConfiguration::StartUpSearchTag() const
        {
            return m_startUpSearchTag;
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

        std::string ApplicationConfiguration::MyPinsPoiSetId() const
        {
            return m_myPinsPoiSetId;
        }

        bool ApplicationConfiguration::IsKioskTouchInputEnabled() const
        {
            return m_isKioskTouchInputEnabled;
        }

        bool ApplicationConfiguration::IsInKioskMode() const
        {
            return m_isInKioskMode;
        }

        bool ApplicationConfiguration::ShouldStartFullscreen() const
        {
            return m_shouldStartFullscreen;
        }
        
        bool ApplicationConfiguration::UseJapaneseFont() const
        {
            return m_useJapaneseFont;
        }
        
        const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& ApplicationConfiguration::InteriorTrackingInfo() const
        {
            return m_interiorTrackingInfo;
        }

        bool ApplicationConfiguration::IsFixedIndoorLocationEnabled() const
        {
            return m_fixedIndoorLocation.GetInteriorId().IsValid();
        }

        const SdkModel::ApplicationFixedIndoorLocation& ApplicationConfiguration::FixedIndoorLocation() const
        {
            return m_fixedIndoorLocation;
        }

        const std::vector<Eegeo::Space::LatLongAltitude>& ApplicationConfiguration::AttractModeTargetSplinePoints() const
        {
            return m_attractModeTargetSplinePoints;
        }

        const std::vector<Eegeo::Space::LatLongAltitude>& ApplicationConfiguration::AttractModePositionSplinePoints() const
        {
            return m_attractModePositionSplinePoints;
        }

        const long long ApplicationConfiguration::AttractModeTimeoutMs() const
        {
            return m_attractModeTimeoutMs;
        }

        const float ApplicationConfiguration::AttractModePlaybackSpeed() const
        {
            return m_attractModePlaybackSpeed;
        }

        const bool ApplicationConfiguration::IsAttractModeEnabled() const
        {
            return m_attractModeTimeoutMs > 0 &&
                   m_attractModeTargetSplinePoints.size() > 0 &&
                   m_attractModePositionSplinePoints.size() >= 2;
        }

        std::string ApplicationConfiguration::OptionsAdminPassword() const
        {
            return m_optionsAdminPassword;
        }
        
        const long long ApplicationConfiguration::SurveyRequirementTimeSec() const
        {
            return m_surveyRequirementTimeSec;
        }
        
        const std::string ApplicationConfiguration::TimerSurveyUrl() const
        {
            return m_timerSurveyUrl;
        }
        
        const std::string ApplicationConfiguration::HockeyAppId() const
        {
            return m_hockeyAppId;
        }

        bool ApplicationConfiguration::HasMapScene() const
        {
            return m_hasMapScene;
        }

        const std::string ApplicationConfiguration::MapSceneId() const
        {
            return m_mapSceneId;
        }

		const std::vector<std::vector<std::string>> ApplicationConfiguration::CustomKeyboardLayout() const
		{
			return m_customKeyboardLayout;
		}

        const std::vector<SdkModel::ApplicationMenuItemTagSearchConfig> ApplicationConfiguration::OutdoorSearchMenuItems() const
        {
            return m_outdoorSearchMenuItems;
        }

        bool ApplicationConfiguration::OverrideIndoorSearchMenuItems() const
        {
            return m_overrideIndoorSearchMenuItems;
        }
    }
}
