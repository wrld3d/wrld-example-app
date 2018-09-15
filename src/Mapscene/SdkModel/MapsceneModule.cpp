// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "MapsceneModule.h"
#include "ILocationProvider.h"

namespace ExampleApp
{
    namespace Mapscene
    {
        namespace SdkModel
        {
            ExampleApp::Mapscene::SdkModel::MapsceneModule::MapsceneModule(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                           Eegeo::Web::IWebLoadRequestFactory& webFactory,
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
                                                                           const ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                           Eegeo::Modules::Map::MapModule& mapModule,
                                                                           LocationProvider::ILocationProvider& locationProvider)
            {
                m_pMapsceneLoader = Eegeo_NEW(MapsceneLoader)(cameraTransitionController,
                                                              webFactory,
                                                              alertBoxFactory,
                                                              defaultConfig,
                                                              manifestLoader,
                                                              manifestNotifier,
                                                              cityThemeLoader,
                                                              cityThemeService,
                                                              interiorMenuObserver,
                                                              searchQueryPerformer,
                                                              aboutPageViewModule,
                                                              navigationService,
                                                              apiTokenService,
                                                              interiorSelectionModel,
                                                              appModeModel,
                                                              mapModule,
                                                              locationProvider);
            }
            
            ExampleApp::Mapscene::SdkModel::MapsceneModule::~MapsceneModule()
            {
                Eegeo_DELETE(m_pMapsceneLoader);
            }
            
           ExampleApp::Mapscene::SdkModel::MapsceneLoader& ExampleApp::Mapscene::SdkModel::MapsceneModule::GetMapsceneLoader()
            {
                return *m_pMapsceneLoader;
            }
        }
    }
}

