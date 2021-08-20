// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationModule.h"
#include "ApplicationConfigurationService.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ApplicationConfigurationReader.h"
#include "IApplicationConfigurationVersionProvider.h"
#include "ConfigSections.h"
#include "IPlatformConfigBuilder.h"
#include "ApiKey.h"

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
                    const std::string emptyYelpApiKey;
                    const std::string emptyGeoNamesUserName;
                    const std::string eegeoSearchServiceUrl = "https://poi.wrld3d.com/v1.1";
                    const std::string emptyMyPinsWebServiceUrl;
                    const std::string emptyMyPinsWebServiceAuthToken;
                    const std::string emptyMyPinsPoiSetId;
                    
                    const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfo;
                    
                    const bool tryStartAtGpsLocation = false;
                    const bool shouldStartFullscreen = false;
                    const bool isKioskTouchInputEnabled = false;
                    const bool isInKioskMode = false;
                    const bool useJapaneseFont = false;
                    const bool useChineseFont = false;
                    
                    const bool shouldPerformStartUpSearch = false;
                    const std::string startUpSearchTag = "";

                    const SdkModel::ApplicationFixedIndoorLocation fixedIndoorLocation(Eegeo::Space::LatLong(0.0, 0.0), "", 0, 180.0, 500.0);

                    const std::vector<Eegeo::Space::LatLongAltitude> attractModeTargetSplinePoints;
                    const std::vector<Eegeo::Space::LatLongAltitude> attractModePositionSplinePoints;
                    const long long attractModeTimeoutDisabled = 0;
                    const float attractModePlaybackSpeed = 0.007f;

                    const std::string emptyOptionsAdminPassword;

                    const float compassCameraOffset = 0.0f;
                    const float compassCameraOffsetTopDown = 0.0f;
                    const bool compassCameraDampingEnabled = false;
                    
                    const long long surveyTimeRequirementSec = 90;
                    
                    const std::string timerSurveyUrl = "";
                    
                    const std::string hockeyAppId = "";
                    const std::string javascriptWhitelistUrl = "";
                    
                    const std::vector<std::vector<std::string>> customKeyboardLayout = {};
                    
                    const std::string startLocationIndoorId = "";
                    const int startLocationFloorIndex = 0;

                    const std::vector<SdkModel::ApplicationMenuItemTagSearchConfig> outdoorSearchMenuItems;
                    bool overrideIndoorSearchMenuItems = false;
                    bool showPoiDirectionsButton = false;

                    bool trafficEnabled = true;

                    return ApplicationConfiguration("Eegeo Example App",
                        emptyEegeoApiKey,
                        productVersion,
                        buildNumber,
                        combinedVersionString,
                        Eegeo::Config::CoverageTreeManifestUrlDefault,
                        Eegeo::Config::CityThemesManifestUrlDefault,
                        "EmbeddedTheme",
                        Eegeo::Space::LatLongAltitude(37.7858f, -122.401f, 2.7),
                        1781.0f,
                        0.f,
                        startLocationIndoorId,
                        startLocationFloorIndex,
                        tryStartAtGpsLocation,
                        shouldStartFullscreen,
                        shouldPerformStartUpSearch,
                        startUpSearchTag,
                        emptyGoogleAnalyticsReferrerToken,
                        emptyFlurryApiKey,
                        emptyYelpApiKey,
                        emptyGeoNamesUserName,
                        eegeoSearchServiceUrl,
                        emptyMyPinsWebServiceUrl,
                        emptyMyPinsWebServiceAuthToken,
                        emptyMyPinsPoiSetId,
                        javascriptWhitelistUrl,
                        isKioskTouchInputEnabled,
                        isInKioskMode,
                        useJapaneseFont,
                        useChineseFont,
                        interiorTrackingInfo,
                        fixedIndoorLocation,
                        attractModeTargetSplinePoints,
                        attractModePositionSplinePoints,
                        attractModeTimeoutDisabled,
                        attractModePlaybackSpeed,
                        emptyOptionsAdminPassword,
                        compassCameraOffset,
                        compassCameraOffsetTopDown,
                        compassCameraDampingEnabled,
                        surveyTimeRequirementSec,
                        timerSurveyUrl,
                        hockeyAppId,
                        false,
                        "",
                        customKeyboardLayout,
                        outdoorSearchMenuItems,
                        overrideIndoorSearchMenuItems,
                        showPoiDirectionsButton,
                        trafficEnabled
                        );
                }

                const std::string defaultFontFilename = "opensans_semibold_sdf.fnt";
                const std::string japanFontFilename = "IPAexGothic_sdf.fnt";
                const std::string chinaFontFilename = "notosans_sdf_china_region.fnt";

                std::string BuildEnvironmentFontFilename(const ApplicationConfiguration& appConfig)
                {
                    if (appConfig.UseJapaneseFont())
                    {
                        return japanFontFilename;
                    }
                    else if (appConfig.UseChineseFont())
                    {
                        return chinaFontFilename;
                    }
                    else
                    {
                        return defaultFontFilename;
                    }
                }

            }
            
            ApplicationConfig::ApplicationConfiguration LoadAppConfig(Eegeo::Helpers::IFileIO& fileIO,
                                                                      ApplicationConfig::SdkModel::IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider,
                                                                      const std::string& configFilePath
                                                                      )
            {
        
                ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationModule applicationConfigurationModule(fileIO,
                                                                                                                       applicationConfigurationVersionProvider
                                                                                                                       );
                return applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration(configFilePath);
            }
            
            Eegeo::Config::PlatformConfig BuildPlatformConfig(Eegeo::Config::IPlatformConfigBuilder& platformConfigBuilder,
                                                              const ApplicationConfiguration& appConfig)
            {
                Eegeo::Config::PlatformConfig platformConfig = platformConfigBuilder.Build();
                platformConfig.CoverageTreeConfig.ManifestUrl = appConfig.CoverageTreeManifestURL();
                platformConfig.CityThemesConfig.StreamedManifestUrl = appConfig.ThemeManifestURL();
                platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = appConfig.EmbeddedThemeTexturePath();

                platformConfig.OptionsConfig.EnableLabels = true;
                const std::string& environmentFontFilename = BuildEnvironmentFontFilename(appConfig);
                
                platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = environmentFontFilename;
                platformConfig.MapLayersConfig.Interiors.UseLegacyLabels = false;
                platformConfig.MapLayersConfig.Interiors.UseLegacyEntryMarkers = false;
                platformConfig.MapLayersConfig.Interiors.LabelCategoryMapPath = "Interiors/label_category_mapping.json";
                platformConfig.MapLayersConfig.LabelsModuleConfig.StyleSheetPath = "Labels/label_style_sheet.json";
                platformConfig.MapLayersConfig.LabelsModuleConfig.CategoryIconMapPath = "Labels/label_category_icon_map.json";
                platformConfig.MapLayersConfig.IconsModuleConfig.IconsEnabled = true;
                platformConfig.MapLayersConfig.IconsModuleConfig.IconSetManifestPath = "SearchResultOnMap/pin_sheet.json";

                platformConfig.MapLayersConfig.Interiors.LabelFontTextureFilename = environmentFontFilename;
                platformConfig.MapLayersConfig.DebugRenderingModuleConfig.DebugFontFilename = defaultFontFilename;
                
                platformConfig.MapLayersConfig.BlueSphereConfig.CreateViews = true;
                platformConfig.MapLayersConfig.TrafficConfig.Enabled = appConfig.IsTrafficEnabled();

                return platformConfig;
            }
            
            ApplicationConfigurationModule::ApplicationConfigurationModule(
                Eegeo::Helpers::IFileIO& fileIO,
                const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider)
            {
                const ApplicationConfiguration& defaultConfig = BuildDefaultConfig(applicationConfigurationVersionProvider);

                m_pApplicationConfigurationReader = Eegeo_NEW(ApplicationConfigurationReader)(fileIO);
                m_pApplicationConfigurationParser = Eegeo_NEW(ApplicationConfigurationJsonParser)(defaultConfig);
                m_pApplicationConfigurationService = Eegeo_NEW(ApplicationConfigurationService)(*m_pApplicationConfigurationParser,
                                                                                                *m_pApplicationConfigurationReader);                    
            }
            
            ApplicationConfigurationModule::~ApplicationConfigurationModule()
            {
                Eegeo_DELETE m_pApplicationConfigurationService;
                Eegeo_DELETE m_pApplicationConfigurationParser;
                Eegeo_DELETE m_pApplicationConfigurationReader;
            }
            
            IApplicationConfigurationService& ApplicationConfigurationModule::GetApplicationConfigurationService()
            {
                return *m_pApplicationConfigurationService;
            }
        }
    }
}
