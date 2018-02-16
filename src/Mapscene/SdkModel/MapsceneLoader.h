// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "CameraTransitions.h"
#include "IAlertBoxFactory.h"
#include "ApplicationConfiguration.h"
#include "CoverageTrees.h"
#include "CityThemes.h"
#include "ISearchQueryPerformer.h"
#include "AboutPageViewModel.h"
#include "InteriorMenuObserver.h"
#include "Location.h"
#include "AppModes.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace Mapscene
    {
        namespace SdkModel
        {
            class MapsceneLoader
            {
            public:
                MapsceneLoader(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
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
                               const ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel);
                ~MapsceneLoader();
                
                void LoadMapscene(const std::string& path, bool shouldDisableStartupSearch);
            private:
                std::string GenerateConfigUrl(const std::string& path) const;
                void HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse);
                void OnFailAlertBoxDismissed();
                
                Eegeo::Helpers::TCallback0<MapsceneLoader> m_newThemeDataCallback;
                void HandleNewThemeManifestLoaded();
                
                Eegeo::Helpers::TCallback1<MapsceneLoader, const Eegeo::Streaming::CoverageTrees::CoverageTreeManifest> m_newManifestCallback;
                void HandleNewCoverageTreeManifestLoaded(const Eegeo::Streaming::CoverageTrees::CoverageTreeManifest& manifest);
                
                Eegeo::Web::TWebLoadRequestCompletionCallback<MapsceneLoader> m_configRequestCompleteCallback;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                const std::string CONFIG_FILES_HOME = "http://mapscene.eegeo.com";
                
                Eegeo::Helpers::TCallback0<MapsceneLoader> m_startupSearchCameraTransitionCompleteCallback;
                std::string m_startupSearchTag;
                Eegeo::Space::LatLongAltitude m_startupSearchLocation;
                bool m_startAtGPSLocation;
                bool m_shouldPerformStartupSearch;
                bool m_shouldDisableStartupSearch;
                void HandleStartupSearchCameraTransitionComplete();
                
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                ApplicationConfig::ApplicationConfiguration& m_defaultConfig;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<MapsceneLoader> m_failAlertHandler;
                Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& m_manifestLoader;
                Eegeo::Streaming::CoverageTrees::CoverageTreeManifestNotifier& m_manifestNotifier;
                Eegeo::Resources::CityThemes::CityThemeLoader& m_cityThemeLoader;
                Eegeo::Resources::CityThemes::ICityThemesService& m_cityThemeService;
                Search::SdkModel::InteriorMenuObserver& m_interiorMenuObserver;
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                AboutPage::View::IAboutPageViewModel& m_aboutPageViewModule;
                Eegeo::Location::NavigationService& m_navigationService;
                Eegeo::Web::ApiTokenService& m_apiTokenService;
                std::string m_previouslyLoadedCoverageTreeUrl;
                std::string m_previouslyLoadedThemeManifestUrl;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                const ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            };
        }
    }
}



