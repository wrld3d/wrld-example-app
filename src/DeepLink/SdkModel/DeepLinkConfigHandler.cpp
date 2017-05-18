// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkConfigHandler.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"
#include "ICameraTransitionController.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ICoverageTreeManifestLoader.h"
#include "CoverageTreeManifestNotifier.h"
#include "ApiTokenService.h"
#include "CityThemeLoader.h"
#include "ICityThemesService.h"
#include "NavigationService.h"
#include "CityThemeData.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkConfigHandler::DeepLinkConfigHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                         Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                         ApplicationConfig::ApplicationConfiguration& defaultConfig,
                                                         Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifestLoader,
                                                         Eegeo::Streaming::CoverageTrees::CoverageTreeManifestNotifier& manifestNotifier,
                                                         Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                                                         Eegeo::Resources::CityThemes::ICityThemesService& cityThemeService,
                                                         Search::SdkModel::InteriorMenuObserver& interiorMenuObserver,
                                                         Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                         AboutPage::View::IAboutPageViewModel& aboutPageViewModule,
                                                         Eegeo::Location::NavigationService& navigationService,
                                                         Eegeo::Web::ApiTokenService& apiTokenService)
            :m_webRequestFactory(webRequestFactory)
            ,m_configRequestCompleteCallback(this, &DeepLinkConfigHandler::HandleConfigResponse)
            ,m_failAlertHandler(this, &DeepLinkConfigHandler::OnFailAlertBoxDismissed)
            ,m_cameraTransitionController(cameraTransitionController)
            ,m_alertBoxFactory(alertBoxFactory)
            ,m_defaultConfig(defaultConfig)
            ,m_manifestLoader(manifestLoader)
            ,m_manifestNotifier(manifestNotifier)
            ,m_cityThemeLoader(cityThemeLoader)
            ,m_cityThemeService(cityThemeService)
            ,m_interiorMenuObserver(interiorMenuObserver)
            ,m_searchQueryPerformer(searchQueryPerformer)
            ,m_aboutPageViewModule(aboutPageViewModule)
            ,m_navigationService(navigationService)
            ,m_apiTokenService(apiTokenService)
            ,m_previouslyLoadedCoverageTreeUrl("")
            ,m_previouslyLoadedThemeManifestUrl("")
            ,m_newManifestCallback(this, &DeepLinkConfigHandler::HandleNewCoverageTreeManifestLoaded)
            ,m_newThemeDataCallback(this, &DeepLinkConfigHandler::HandleNewThemeManifestLoaded)
            {
                m_manifestNotifier.AddManifestLoadedObserver(m_newManifestCallback);
                m_cityThemeService.SubscribeSharedThemeDataChanged(m_newThemeDataCallback);
            }

            DeepLinkConfigHandler::~DeepLinkConfigHandler()
            {
                m_cityThemeService.UnsubscribeSharedThemeDataChanged(m_newThemeDataCallback);
                m_manifestNotifier.RemoveManifestLoadedObserver(m_newManifestCallback);
            }
            
            void DeepLinkConfigHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                const std::string url = GenerateConfigUrl(data);
                Eegeo::Web::IWebLoadRequest* webRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_configRequestCompleteCallback).Build();
                webRequest->Load();
            }

            std::string DeepLinkConfigHandler::GenerateConfigUrl(const AppInterface::UrlData& data) const
            {
                return CONFIG_FILES_HOME + data.path + "/manifest";
            }
            
            void DeepLinkConfigHandler::HandleNewCoverageTreeManifestLoaded(const Eegeo::Streaming::CoverageTrees::CoverageTreeManifest& manifest)
            {
                m_previouslyLoadedCoverageTreeUrl = manifest.ManifestUrl;
            }
            
            void DeepLinkConfigHandler::HandleNewThemeManifestLoaded()
            {
                m_previouslyLoadedThemeManifestUrl = m_cityThemeService.GetSharedThemeData().ManifestUrl;
            }

            void DeepLinkConfigHandler::HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse)
            {
                if(webResponse.IsSucceeded())
                {
                    ApplicationConfig::SdkModel::ApplicationConfigurationJsonParser parser(m_defaultConfig);
                    size_t resultSize = webResponse.GetBodyData().size();
                    std::string resultString = std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);

                    if(parser.IsValidConfig(resultString))
                    {
                        ApplicationConfig::ApplicationConfiguration applicationConfig = parser.ParseConfiguration(resultString);
                        m_apiTokenService.ApiKeyChanged(applicationConfig.EegeoApiKey());
                        if(applicationConfig.CoverageTreeManifestURL() != m_previouslyLoadedCoverageTreeUrl)
                        {
                            m_manifestLoader.LoadCoverageTreeManifest(applicationConfig.CoverageTreeManifestURL());
                        }
                        
                        const std::string themeNameContains = "Summer";
                        const std::string themeStateName = "DayDefault";
                        if(applicationConfig.ThemeManifestURL() != m_previouslyLoadedThemeManifestUrl)
                        {
                            m_cityThemeLoader.LoadThemes(applicationConfig.ThemeManifestURL(), themeNameContains, themeStateName);
                        }
                        
                        const float newHeading = Eegeo::Math::Deg2Rad(applicationConfig.OrientationDegrees());
                        m_cameraTransitionController.StartTransitionTo(applicationConfig.InterestLocation().ToECEF(), applicationConfig.DistanceToInterestMetres(), newHeading);
                        m_interiorMenuObserver.UpdateDefaultOutdoorSearchMenuItems(applicationConfig.RawConfig());
                        m_aboutPageViewModule.UpdateApplicationName(applicationConfig.Name());

                        const std::string TryStartAtGpsLocation = "try_start_at_gps_location";
                        const bool mapsceneSpecifiesGpsStart = parser.HasKey(resultString, TryStartAtGpsLocation);
                        const bool useGps = mapsceneSpecifiesGpsStart && applicationConfig.TryStartAtGpsLocation();
                        if (useGps)
                        {
                            m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeFollow);
                        }
                        else
                        {
                            m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                        }
                        
                        const std::string PerformStartUpSearch = "perform_start_up_search";
                        const bool mapsceneSpecifiesStartUpSearch = parser.HasKey(resultString, PerformStartUpSearch);
                        const bool shouldPerformStartUpSearch = mapsceneSpecifiesStartUpSearch && applicationConfig.ShouldPerformStartUpSearch();
                        if (shouldPerformStartUpSearch)
                        {
                            m_searchQueryPerformer.PerformSearchQuery(applicationConfig.StartUpSearchTag(), true, false, applicationConfig.InterestLocation());
                        }
                    }
                    else
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("User config file invalid", "Reverting to default config",m_failAlertHandler);
                    }
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("User config load failed", "Reverting to default config",m_failAlertHandler);
                }
            }

            void DeepLinkConfigHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}
