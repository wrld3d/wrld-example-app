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

                    return ApplicationConfiguration ("Eegeo Example App", 
                        emptyEegeoApiKey,
                        Eegeo::Space::LatLongAltitude(0.0f, 0.0f, 0.0f),
                        1000.f,
                        0.f,
                        false,
                        false,
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
                        false,
                        "EmbeddedTheme",
                        emptyTwitterAuthCode,
                        false,
                        interiorTrackingInfo);
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

                platformConfig.OptionsConfig.EnableLabels = appConfig.UseLabels();
                platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = appConfig.UseLabels() ? "IPAexGothic_sdf.fnt" : "IPAexGothic32_A8_icons.fnt";
                
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
