// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapsceneLoader.h"
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
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Mapscene
    {
        namespace SdkModel
        {
            MapsceneLoader::MapsceneLoader(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
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
                                           Eegeo::Web::ApiTokenService& apiTokenService,
                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           const ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel)
            :m_webRequestFactory(webRequestFactory)
            ,m_configRequestCompleteCallback(this, &MapsceneLoader::HandleConfigResponse)
            ,m_failAlertHandler(this, &MapsceneLoader::OnFailAlertBoxDismissed)
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
            ,m_newManifestCallback(this, &MapsceneLoader::HandleNewCoverageTreeManifestLoaded)
            ,m_newThemeDataCallback(this, &MapsceneLoader::HandleNewThemeManifestLoaded)
            ,m_interiorSelectionModel(interiorSelectionModel)
            ,m_appModeModel(appModeModel)
            ,m_startupSearchTag("")
            ,m_startupSearchLocation(0, 0, 0)
            ,m_shouldPerformStartupSearch(false)
            ,m_shouldDisableStartupSearch(false)
            ,m_startAtGPSLocation(false)
            ,m_startupSearchCameraTransitionCompleteCallback(this, &MapsceneLoader::HandleStartupSearchCameraTransitionComplete)
            {
                m_manifestNotifier.AddManifestLoadedObserver(m_newManifestCallback);
                m_cityThemeService.SubscribeSharedThemeDataChanged(m_newThemeDataCallback);
                m_cameraTransitionController.InsertTransitionCompletedCallback(m_startupSearchCameraTransitionCompleteCallback);
            }
            
            MapsceneLoader::~MapsceneLoader()
            {
                m_cityThemeService.UnsubscribeSharedThemeDataChanged(m_newThemeDataCallback);
                m_manifestNotifier.RemoveManifestLoadedObserver(m_newManifestCallback);
                m_cameraTransitionController.RemoveTransitionCompletedCallback(m_startupSearchCameraTransitionCompleteCallback);
            }
            
            void MapsceneLoader::LoadMapscene(const std::string& path, bool shouldDisableStartupSearch)
            {
                const std::string url = GenerateConfigUrl(path);
                m_shouldDisableStartupSearch = shouldDisableStartupSearch;
                Eegeo::Web::IWebLoadRequest* webRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_configRequestCompleteCallback).Build();
                webRequest->Load();
            }
            
            void MapsceneLoader::HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse)
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
                        if(m_appModeModel.GetAppMode() != ExampleApp::AppModes::SdkModel::InteriorMode)
                        {
                            m_interiorSelectionModel.ClearSelection();
                        }
                        
                        bool jumpIfFar = true;
                        bool setGpsModeOff = true;
                        bool setInteriorHeading = true;
                        m_cameraTransitionController.StartTransitionTo(applicationConfig.InterestLocation().ToECEF(), applicationConfig.DistanceToInterestMetres(), newHeading, applicationConfig.IndoorId(), applicationConfig.FloorIndex(), jumpIfFar, setGpsModeOff, setInteriorHeading);
                        m_interiorMenuObserver.UpdateDefaultOutdoorSearchMenuItems(applicationConfig.OutdoorSearchMenuItems(), applicationConfig.OverrideIndoorSearchMenuItems());
                        m_aboutPageViewModule.UpdateApplicationName(applicationConfig.Name());
                        
                        const std::string TryStartAtGpsLocation = "try_start_at_gps_location";
                        const bool mapsceneSpecifiesGpsStart = parser.HasKey(resultString, TryStartAtGpsLocation);
                        m_startAtGPSLocation = mapsceneSpecifiesGpsStart && applicationConfig.TryStartAtGpsLocation();
                        if (m_startAtGPSLocation)
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
                        
                        if(!m_shouldDisableStartupSearch)
                        {
                            if (shouldPerformStartUpSearch)
                            {
                                m_startupSearchTag = applicationConfig.StartUpSearchTag();
                                m_startupSearchLocation = applicationConfig.InterestLocation();
                                m_shouldPerformStartupSearch = true;
                            }
                            else
                            {
                                m_searchQueryPerformer.RemoveSearchQueryResults();
                            }
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
            
            std::string MapsceneLoader::GenerateConfigUrl(const std::string& path) const
            {
                return CONFIG_FILES_HOME + path + "/manifest";
            }
            
            void MapsceneLoader::OnFailAlertBoxDismissed()
            { //Do nothing
            }
            
            void MapsceneLoader::HandleNewThemeManifestLoaded()
            {
                m_previouslyLoadedThemeManifestUrl = m_cityThemeService.GetSharedThemeData().ManifestUrl;
            }
            
            void MapsceneLoader::HandleNewCoverageTreeManifestLoaded(const Eegeo::Streaming::CoverageTrees::CoverageTreeManifest& manifest)
            {
                m_previouslyLoadedCoverageTreeUrl = manifest.ManifestUrl;
            }
            
            void MapsceneLoader::HandleStartupSearchCameraTransitionComplete()
            {
                if(m_shouldPerformStartupSearch)
                {
                    m_shouldPerformStartupSearch = false;
                    m_searchQueryPerformer.PerformSearchQuery(m_startupSearchTag, true, false, m_startupSearchLocation, m_startAtGPSLocation);
                }
                
            }
        }
    }
}




