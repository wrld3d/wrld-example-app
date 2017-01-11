// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationModule.h"
#include "ApplicationConfigurationService.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ApplicationConfigurationReader.h"
#include "ApplicationConfigurationBuilder.h"
#include "IApplicationConfigurationVersionProvider.h"
#include "ConfigSections.h"
#include "IPlatformConfigBuilder.h"
#include "ApiKey.h"
#include "ApplicationConfigurationXorCipher.h"

#include "base64.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                ApplicationConfiguration BuildDefaultConfig(const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider)
                {
                    // please see ./README.md and comments in ./src/ApiKey.h for instructions on how to obtain an EegeoApiKey and set via the app config file
                    const std::string emptyEegeoApiKey;
                    const std::string& productVersion = applicationConfigurationVersionProvider.GetProductVersionString();
                    const std::string& buildNumber = applicationConfigurationVersionProvider.GetProductVersionString();
                    const std::string& combinedVersionString = productVersion + "." + buildNumber;
                    const std::string emptyGoogleAnalyticsReferrerToken;
                    const std::string emptyFlurryApiKey;
                    const std::string emptyYelpConsumerKey;
                    const std::string emptyYelpConsumerSecret;
                    const std::string emptyYelpOAuthToken;
                    const std::string emptyYelpOAuthTokenSecret;
                    const std::string emptyGeoNamesUserName;
                    const std::string eegeoSearchServiceUrl = "https://poi.eegeo.com/v1.1";
                    const std::string emptyMyPinsWebServiceUrl;
                    const std::string emptyMyPinsWebServiceAuthToken;
                    const std::string emptyTwitterAuthCode;

                    const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*> buildingsInfo;
                    const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*> restrictedBuildingsInfo;

                    const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfo;
                    
                    const bool tryStartAtGpsLocation = false;
                    const bool shouldStartFullscreen = false;
                    const bool isKioskTouchInputEnabled = false;
                    const bool isInKioskMode = false;
                    const bool useLabels = false;
                    const bool useJapaneseFont = false;

                    const double attractModePlaybackSpeed = 0.03;

                    return ApplicationConfiguration ("Eegeo Example App", 
                        emptyEegeoApiKey,
                        Eegeo::Space::LatLongAltitude(0.0f, 0.0f, 0.0f),
                        1000.f,
                        0.f,
                        tryStartAtGpsLocation,
                        shouldStartFullscreen,
                        emptyGoogleAnalyticsReferrerToken,
                        emptyFlurryApiKey,
                        emptyYelpConsumerKey,
                        emptyYelpConsumerSecret,
                        emptyYelpOAuthToken,
                        emptyYelpOAuthTokenSecret,
                        emptyGeoNamesUserName,
                        Eegeo::Config::CoverageTreeManifestUrlDefault,
                        Eegeo::Config::CityThemesManifestUrlDefault,
                        "",
                        eegeoSearchServiceUrl,
                        emptyMyPinsWebServiceUrl,
                        emptyMyPinsWebServiceAuthToken,
                        productVersion,
                        buildNumber,
                        combinedVersionString,
                        false,
                        "",
                        0,
                        "",
                        buildingsInfo,
                        restrictedBuildingsInfo,
                        isKioskTouchInputEnabled,
                        isInKioskMode,
                        "EmbeddedTheme",
                        emptyTwitterAuthCode,
                        useLabels,
                        useJapaneseFont,
                        interiorTrackingInfo,
                        Eegeo::Space::LatLong(0.0, 0.0),
                        "",
                        0,
                        180.0,
                        std::vector<Eegeo::Space::LatLongAltitude>(),
                        std::vector<Eegeo::Space::LatLongAltitude>(),
                        0,
                        attractModePlaybackSpeed);
                }
            }
            
            ApplicationConfig::ApplicationConfiguration LoadAppConfig(Eegeo::Helpers::IFileIO& fileIO,
                                                                      ApplicationConfig::SdkModel::IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider,
                                                                      const std::string& configFilePath,
                                                                      const std::string& configKeyBase64)
            {
                
                ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationModule applicationConfigurationModule(fileIO,
                                                                                                                       applicationConfigurationVersionProvider,
                                                                                                                       configKeyBase64);
                return applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration(configFilePath);
            }
            
            Eegeo::Config::PlatformConfig BuildPlatformConfig(Eegeo::Config::IPlatformConfigBuilder& platformConfigBuilder,
                                                              const ApplicationConfiguration& appConfig)
            {
                Eegeo::Config::PlatformConfig platformConfig = platformConfigBuilder.Build();
                platformConfig.CoverageTreeConfig.ManifestUrl = appConfig.CoverageTreeManifestURL();
                platformConfig.CityThemesConfig.StreamedManifestUrl = appConfig.ThemeManifestURL();
                platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = appConfig.EmbeddedThemeTexturePath();

                if (appConfig.UseLabels())
                {
                    platformConfig.OptionsConfig.EnableLabels = true;
                    platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = appConfig.UseJapaneseFont() ? "IPAexGothic_sdf.fnt" : "opensans_semibold_sdf.fnt";
                    platformConfig.MapLayersConfig.Interiors.UseLegacyLabels = false;
                    platformConfig.MapLayersConfig.Interiors.LabelCategoryMapPath = "Interiors/label_category_mapping.json";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.StyleSheetPath = "Labels/label_style_sheet.json";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.CategoryIconMapPath = "Labels/label_category_icon_map.json";
                }
                else
                {
                    platformConfig.OptionsConfig.EnableLabels = false;
                    platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = appConfig.UseJapaneseFont() ? "IPAexGothic32_A8_icons.fnt" : "FrankBold50_A8_icons.fnt";
                    platformConfig.MapLayersConfig.Interiors.UseLegacyLabels = true;
                    platformConfig.MapLayersConfig.Interiors.LabelCategoryMapPath = "";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.StyleSheetPath = "";
                    
                }

                platformConfig.OptionsConfig.InteriorsAffectedByFlattening = false;

                platformConfig.MapLayersConfig.Interiors.LabelsVisibleWhenExpanded = true;

                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedFloorSpacingFactor = 0.15f;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedSelectedFloorGapFactor = 9.0f;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.FloorScaleWhenSelected = 2.0f;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedDeadZone = 0.2f;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedLookAtDeadZone = 0.2f;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.UseBoundsMaxDimension = true;
                platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.UseLargeFloorGapForSmallFloorCount = false;

                return platformConfig;
            }
            
            ApplicationConfigurationModule::ApplicationConfigurationModule(Eegeo::Helpers::IFileIO& fileIO,
                                                                           const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider,
                                                                           const std::string& configKeyBase64)
            {
                const ApplicationConfiguration& defaultConfig = BuildDefaultConfig(applicationConfigurationVersionProvider);

                const std::string& configKey = base64_decode(configKeyBase64);
                m_pApplicationConfigurationEncryption = Eegeo_NEW(ApplicationConfigurationXorCipher)(configKey);
                m_pApplicationConfigurationBuilder = Eegeo_NEW(ApplicationConfigurationBuilder)(*m_pApplicationConfigurationEncryption, configKey);
                m_pApplicationConfigurationReader = Eegeo_NEW(ApplicationConfigurationReader)(fileIO);
                m_pApplicationConfigurationParser = Eegeo_NEW(ApplicationConfigurationJsonParser)(defaultConfig,
                                                                                                  *m_pApplicationConfigurationBuilder);
                m_pApplicationConfigurationService = Eegeo_NEW(ApplicationConfigurationService)(*m_pApplicationConfigurationParser,
																								*m_pApplicationConfigurationReader);
            }
            
            ApplicationConfigurationModule::~ApplicationConfigurationModule()
            {
                Eegeo_DELETE m_pApplicationConfigurationService;
                Eegeo_DELETE m_pApplicationConfigurationParser;
                Eegeo_DELETE m_pApplicationConfigurationReader;
                Eegeo_DELETE m_pApplicationConfigurationBuilder;
                Eegeo_DELETE m_pApplicationConfigurationEncryption;
            }
            
            IApplicationConfigurationService& ApplicationConfigurationModule::GetApplicationConfigurationService()
            {
                return *m_pApplicationConfigurationService;
            }
        }
    }
}
