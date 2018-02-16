// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "Mapscene.h"
#include "MapsceneLoader.h"

namespace ExampleApp
{
    namespace Mapscene
    {
        namespace SdkModel
        {
            class MapsceneModule: private Eegeo::NonCopyable
            {
            public:
                
                MapsceneModule(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
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
                
                ~MapsceneModule();
                
                MapsceneLoader& GetMapsceneLoader();
            private:
                MapsceneLoader* m_pMapsceneLoader;
            };
        }
    }
}

