// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "AutomatedScreenshotController.h"
#include "CallbackCollection.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ICallback.h"
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

namespace ExampleApp
{
    namespace Automation
    {
        class AutomatedScreenshotController : private Eegeo::NonCopyable
        {
        public:
            AutomatedScreenshotController(const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
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
                                          Eegeo::EegeoWorld& eegeoWorld);

            bool NextScene();
            void Update(const float dt);

            void InsertCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback);
            void RemoveCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback);

        private:
            const std::array<std::function<std::function<bool()>()>, 2> States() const;
            const unsigned long NumStates() const;
            std::function<bool()> SetupState(const unsigned long state);
            bool Done() const;

            const ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
            const Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
            Eegeo::Traffic::PlaneSimulation& m_planeSimulation;
            ExampleApp::PlaceJumps::SdkModel::IPlaceJumpController& m_placeJumpController;
            ExampleApp::WeatherMenu::SdkModel::IWeatherController& m_weatherController;
            ExampleApp::Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;
            ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
            Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorCameraController;
            ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
            Eegeo::Streaming::StreamingController& m_streamingController;
            IScreenshotService& m_screenshotService;
            Eegeo::EegeoWorld& m_eegeoWorld;
            int m_updateCyclesToWait;
            std::function<bool()> m_waitPredicate;
            int m_execState;
            unsigned long m_sceneIndex;

            Eegeo::Helpers::CallbackCollection0 m_completedScreenshotsCallbacks;
        };
    }
}
