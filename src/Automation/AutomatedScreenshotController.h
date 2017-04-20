// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "AutomatedScreenshotController.h"
#include "CallbackCollection.h"
#include "CameraTransitionService.h"
#include "CityThemesModule.h"
#include "CityThemes.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ICallback.h"
#include "ICityThemeChangedObserver.h"
#include "IFlattenButtonModel.h"
#include "InteriorsExplorerController.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"
#include "IPlaceJumpController.h"
#include "IScreenshotService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultPoiViewModel.h"
#include "IWeatherController.h"
#include "PlaneSimulation.h"
#include "Streaming.h"
#include "IAppCameraModule.h"

namespace ExampleApp
{
    namespace Automation
    {
        class AutomatedScreenshotController : private Eegeo::NonCopyable
        {
        public:
            AutomatedScreenshotController(const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                          ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionController,
                                          const Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                          Eegeo::Traffic::PlaneSimulation& planeSimulation,
                                          ExampleApp::PlaceJumps::SdkModel::IPlaceJumpController& placeJumpController,
                                          ExampleApp::WeatherMenu::SdkModel::IWeatherController& weatherController,
                                          ExampleApp::Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                          ExampleApp::FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                                          ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                          Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          Eegeo::Resources::Interiors::InteriorsCameraController& interiorCameraController,
                                          ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                          Eegeo::Streaming::StreamingController& streamingController,
                                          IScreenshotService& screenshotService,
                                          Eegeo::EegeoWorld& eegeoWorld,
                                          ExampleAppMessaging::TMessageBus& messageBus,
                                          AppCamera::SdkModel::IAppCameraModule& appCameraModule,
                                          Eegeo::Rendering::ScreenProperties& screenProperties,
                                          ExampleApp::WorldPins::SdkModel::IWorldPinsModule& worldPinsModule);

            bool NextScene();
            void Update(const float dt);

            void InsertCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback);
            void RemoveCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback);

            typedef std::function<bool()> WaitPredicate;
            typedef std::function<WaitPredicate()> SceneSetupFunction;

        private:
            static const int NumScenes = 7;
            const std::array<SceneSetupFunction, NumScenes> States() const;
            std::function<bool()> SetupState(const unsigned long state);
            bool Done() const;

            WaitPredicate SharedLandmarkSceneWaitPredicate(const bool openSearchMenu) const;
            WaitPredicate TabletVASceneSetup(bool openSearchMenu) const;
            WaitPredicate PhoneNYCSceneSetup(bool openSearchMenu) const;
            WaitPredicate SelectedPinSceneSetup(const std::string& query, int searchMenuPinIx) const;

            Eegeo::Traffic::PlaneSimulation& m_planeSimulation;
            ExampleApp::PlaceJumps::SdkModel::IPlaceJumpController& m_placeJumpController;
            ExampleApp::WeatherMenu::SdkModel::IWeatherController& m_weatherController;
            ExampleApp::Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;
            IScreenshotService& m_screenshotService;
            Eegeo::EegeoWorld& m_eegeoWorld;
            int m_updateCyclesToWait;
            std::function<bool()> m_waitPredicate;
            int m_execState;
            unsigned long m_sceneIndex;
            Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            Eegeo::Resources::CityThemes::CityThemeLoader& m_cityThemeLoader;
            Eegeo::Resources::CityThemes::ICityThemesService& m_cityThemesService;
            Eegeo::Resources::CityThemes::ICityThemesUpdater& m_cityThemesUpdater;
            ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Rendering::ScreenProperties& m_screenProperties;
            ExampleApp::WorldPins::SdkModel::IWorldPinsModule& m_worldPinsModule;
            ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& m_cameraTransitionService;

            Eegeo::Helpers::CallbackCollection0 m_completedScreenshotsCallbacks;
        };
    }
}
