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
                    const std::string emptyYelpConsumerKey;
                    const std::string emptyYelpConsumerSecret;
                    const std::string emptyYelpOAuthToken;
                    const std::string emptyYelpOAuthTokenSecret;
                    const std::string emptyGeoNamesUserName;
                    const std::string eegeoSearchServiceUrl = "http://poi.eegeo.com/v1";
                    const std::string emptyMyPinsWebServiceUrl;
                    const std::string emptyMyPinsWebServiceAuthToken;
                    const std::string emptyTwitterAuthCode;

                    return ApplicationConfiguration ("Eegeo Example App", 
                        emptyEegeoApiKey,
                        productVersion,
                        buildNumber,
                        combinedVersionString,
                        Eegeo::Config::CoverageTreeManifestUrlDefault,
                        Eegeo::Config::CityThemesManifestUrlDefault,
                        "Textures/EmbeddedTheme",
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
                        eegeoSearchServiceUrl,
                        emptyMyPinsWebServiceUrl,
                        emptyMyPinsWebServiceAuthToken,
                        emptyTwitterAuthCode,
                        false);
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
