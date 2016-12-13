// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationBuilder.h"
#include "IApplicationConfigurationCipher.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"

#include "HMAC_SHA1.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>


namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationBuilder::ApplicationConfigurationBuilder(const IApplicationConfigurationCipher& cipher,
                                                                            const std::string& configKey)
            : m_cipher(cipher)
            , m_configKey(configKey)
            , m_name("")
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
            , m_eegeoSearchServiceUrl("")
            , m_myPinsWebServiceUrl("")
            , m_myPinsWebServiceAuthToken("")
            , m_webProxyEnabled(false)
            , m_webProxyIpAddress("")
            , m_webProxyPort(0)
            , m_webProxyIgnorePattern("")
            , m_isKioskTouchInputEnabled(false)
            , m_shouldStartFullscreen(false)
            , m_embeddedThemeTexturePath("")
            , m_twitterAuthCode("")
            , m_useLabels(false)
            , m_useJapaneseFonts(false)
            , m_fixedLatlong(0.0, 0.0)
            , m_fixedFloorIndex(0)
            , m_fixedHeadingDegrees(0.0)
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
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetSearchServiceUrl(const std::string& eegeoSearchServiceUrl)
            {
                m_eegeoSearchServiceUrl = eegeoSearchServiceUrl;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetMyPinsWebServiceUrl(const std::string& myPinsWebServiceUrl)
            {
                m_myPinsWebServiceUrl = myPinsWebServiceUrl;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetMyPinsWebServiceAuthToken(const std::string& myPinsWebServiceAuthToken)
            {
                m_myPinsWebServiceAuthToken = myPinsWebServiceAuthToken;
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
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetWebProxyEnabled(bool webProxyEnabled)
            {
                m_webProxyEnabled = webProxyEnabled;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetWebProxyIpAddress(const std::string& webProxyIpAddress)
            {
                m_webProxyIpAddress = webProxyIpAddress;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetWebProxyPort(int webProxyPort)
            {
                m_webProxyPort = webProxyPort;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetWebProxyIgnorePattern(const std::string& webProxyIgnorePattern)
            {
                m_webProxyIgnorePattern = webProxyIgnorePattern;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&infoBuildingList){
                m_buildingsInfo = infoBuildingList;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetRestrictedBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingInfo)
            {
                m_restrictedBuildingsInfo = restrictedBuildingInfo;
                return *this;
            }
            
            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetShouldStartFullscreen(bool startFullscreen)
            {
                m_shouldStartFullscreen = startFullscreen;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetIsKioskTouchInputEnabled(bool kioskTouchInputEnabled)
            {
                m_isKioskTouchInputEnabled = kioskTouchInputEnabled;
                return *this;
            }

			IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetIsInKioskMode(bool isInKioskMode)
			{
				m_isInKioskMode = isInKioskMode;
				return *this;
			}

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetEmbeddedThemeTexturePath(const std::string& embeddedThemeTexturePath)
            {
                m_embeddedThemeTexturePath = embeddedThemeTexturePath;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetTwitterAuthCode(const std::string& twitterAuthCode)
            {
                m_twitterAuthCode = twitterAuthCode;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetUseLabels(bool useLabels)
            {
                m_useLabels = useLabels;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetInteriorTrackingInfo(const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo)
            {
                m_interiorTrackingInfo = interiorTrackingInfo;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetFixedIndoorLocation(const Eegeo::Space::LatLong latlong, const std::string& interiorId, const int floorIndex, const double headingDegrees)
            {
                m_fixedLatlong = latlong;
                m_fixedInteriorId = interiorId;
                m_fixedFloorIndex = floorIndex;
                m_fixedHeadingDegrees = headingDegrees;
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetAttractModeTargetSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points)
            {
                m_attractModeTargetSplinePoints = std::move(points);
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetAttractModePositionSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points)
            {
                m_attractModePositionSplinePoints = std::move(points);
                return *this;
            }

            IApplicationConfigurationBuilder& ApplicationConfigurationBuilder::SetAttractModeTimeoutMs(const long long timeoutMs)
            {
                m_attractModeTimeoutMs = timeoutMs;
                return *this;
            }

            std::string ApplicationConfigurationBuilder::Decrypt(const std::string& value) const
            {
                return m_cipher.Decrypt(value);
            }

            bool ApplicationConfigurationBuilder::ValidateHMAC(const std::string& message, const std::string& hmac) const
            {
                BYTE digest[CHMAC_SHA1::SHA1_DIGEST_LENGTH];
                CHMAC_SHA1().HMAC_SHA1((BYTE*)message.data(), (int)message.size(), (BYTE*)m_configKey.data(), (int)m_configKey.size(), digest);

                std::stringstream hexDigestSS;
                hexDigestSS << std::hex << std::setfill('0');

                for (int i = 0; i < CHMAC_SHA1::SHA1_DIGEST_LENGTH; i++)
                {
                    hexDigestSS << std::setw(2) << static_cast<unsigned>(digest[i]);
                }

                return (hexDigestSS.str() == hmac);
            }
            
            ApplicationConfiguration ApplicationConfigurationBuilder::Build()
            {
                return ApplicationConfiguration(m_name,
                                                m_eegeoApiKey,
                                                m_interestLocation,
                                                m_distanceToInterestMetres,
                                                m_orientationDegrees,
                                                m_tryStartAtGpsLocation,
                                                m_shouldStartFullscreen,
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
                                                m_eegeoSearchServiceUrl,
                                                m_myPinsWebServiceUrl,
                                                m_myPinsWebServiceAuthToken,
                                                m_productVersion,
                                                m_buildNumber,
                                                m_combinedVersionString,
                                                m_webProxyEnabled,
                                                m_webProxyIpAddress,
                                                m_webProxyPort,
                                                m_webProxyIgnorePattern,
                                                m_buildingsInfo,
                                                m_restrictedBuildingsInfo,
                                                m_isKioskTouchInputEnabled,
                                                m_isInKioskMode,
                                                m_embeddedThemeTexturePath,
                                                m_twitterAuthCode,
                                                m_useLabels,
                                                m_useJapaneseFonts,
                                                m_interiorTrackingInfo,
                                                m_fixedLatlong,
                                                m_fixedInteriorId,
                                                m_fixedFloorIndex,
                                                m_fixedHeadingDegrees,
                                                m_attractModeTargetSplinePoints,
                                                m_attractModePositionSplinePoints,
                                                m_attractModeTimeoutMs);
            }
        }
    }
}
