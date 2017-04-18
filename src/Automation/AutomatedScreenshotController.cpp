// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <array>
#include <functional>

#include "ApplicationConfig.h"
#include "AutomatedScreenshotController.h"
#include "CityThemeLoader.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "ICityThemesService.h"
#include "ICityThemesUpdater.h"
#include "IFlattenButtonModel.h"
#include "InteriorsCameraController.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"
#include "IPlaceJumpController.h"
#include "IScreenshotService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultPoiViewModel.h"
#include "IWeatherController.h"
#include "OpenSearchMenuMessage.h"
#include "PlaneSimulation.h"
#include "StreamingController.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace
        {
            const int UpdateCyclesToWaitForSplashScreenToDisappear = 30;
            const int UpdateCyclesPerScreenshot = 15;

            enum {
                ExecStateStreamingInitialSceneAndManifest,
                ExecStateWaitingForSceneToStream,
                ExecStateWaitForSceneToRender,
                ExecStatePrepareNextScene,
                ExecStateDone
            };

            const AutomatedScreenshotController::WaitPredicate NoWait([]() { return true; });
            const AutomatedScreenshotController::WaitPredicate WaitMs(const long long msToWait)
            {
                const long long currentMillis = Eegeo::Helpers::Time::MillisecondsSinceEpoch();
                return [=]() {
                    return Eegeo::Helpers::Time::MillisecondsSinceEpoch() - currentMillis > msToWait;
                };
            }

            template <typename T, typename... Args>
            const AutomatedScreenshotController::WaitPredicate WaitForStreaming(const T* t, const Args... args)
            {
                return [=]() { return !t->IsStreaming(args...); };
            }

            template <typename F>
            const AutomatedScreenshotController::WaitPredicate Act(F f)
            {
                return [=]() {
                    f();
                    return true;
                };
            }

            const AutomatedScreenshotController::WaitPredicate Then(AutomatedScreenshotController::WaitPredicate p1, AutomatedScreenshotController::WaitPredicate p2)
            {
                bool p1Done = false;
                return [=]() mutable {
                    if (!p1Done)
                    {
                        p1Done = p1();
                        return false;
                    }
                    else
                    {
                        return p2();
                    }
                };
            }
            template <typename P>
            const AutomatedScreenshotController::WaitPredicate Seq(P p)
            {
                return p;
            }

            template <typename P, typename... Ps>
            const AutomatedScreenshotController::WaitPredicate Seq(P p, Ps... ps)
            {
                return Then(p, Seq(ps...));
            }
        }

        AutomatedScreenshotController::AutomatedScreenshotController(const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                                     ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                     const Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                                                     Eegeo::Traffic::PlaneSimulation &planeSimulation,
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
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
        : m_planeSimulation(planeSimulation)
        , m_placeJumpController(placeJumpController)
        , m_weatherController(weatherController)
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_flattenButtonModel(flattenButtonModel)
        , m_screenshotService(screenshotService)
        , m_eegeoWorld(eegeoWorld)
        , m_updateCyclesToWait(UpdateCyclesPerScreenshot)
        , m_execState(ExecStateStreamingInitialSceneAndManifest)
        , m_sceneIndex(0)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_interiorsExplorerModel(interiorsExplorerModel)
        , m_cityThemeLoader(eegeoWorld.GetCityThemesModule().GetCityThemeLoader())
        , m_cityThemesService(eegeoWorld.GetCityThemesModule().GetCityThemesService())
        , m_cityThemesUpdater(eegeoWorld.GetCityThemesModule().GetCityThemesUpdater())
        , m_globeCameraController(globeCameraController)
        , m_messageBus(messageBus)
        {
            m_planeSimulation.SetEnabled(false);
        }

        AutomatedScreenshotController::~AutomatedScreenshotController()
        {
        }

        bool AutomatedScreenshotController::NextScene()
        {
            if (m_sceneIndex < NumScenes())
            {
                m_waitPredicate = SetupState(m_sceneIndex);
                m_sceneIndex++;
                return true;
            }
            else
            {
                return false;
            }
        }

        const std::array<AutomatedScreenshotController::SceneSetupFunction, 5> AutomatedScreenshotController::States() const
        {
            return {{
                [this]() {
                    const PlaceJumps::View::PlaceJumpModel London(
                            "London",
                            Eegeo::Space::LatLong::FromDegrees(51.509471, -0.082125),
                            155.0f,
                            2000.0f,
                            "");

                    m_flattenButtonModel.Unflatten();
                    m_placeJumpController.JumpTo(London);
                    m_weatherController.SetTime("Day");
                    m_weatherController.SetTheme("Summer");

                    return WaitMs(10000);
                },

                [this]() {
                    const long long WaitMsForInteriorToLoad = 4000;
                    const Eegeo::Resources::Interiors::InteriorId WestportHouseInteriorId("westport_house");
                    const PlaceJumps::View::PlaceJumpModel WestportHouse(
                            "WestportHouse",
                            Eegeo::Space::LatLong::FromDegrees(56.459905, -2.977996),
                            335.0f,
                            500.0f,
                            "");

                    m_placeJumpController.JumpTo(WestportHouse);

                    return Seq(WaitMs(WaitMsForInteriorToLoad),
                               Act([=]() { m_interiorSelectionModel.SelectInteriorId(WestportHouseInteriorId); }),
                               WaitMs(8000));
                },

                [this]() {
                    const long long MsToWaitForSearchResultsToReturn = 3000;
                    const long long MsToWaitForSearchMenuToOpen = 5000;
                    const PlaceJumps::View::PlaceJumpModel VA(
                            "V&A",
                            Eegeo::Space::LatLong::FromDegrees(51.496592, -0.171757),
                            0.0f,
                            1000.0f,
                            "");

                    m_placeJumpController.JumpTo(VA);
                    m_searchQueryPerformer.PerformSearchQuery("", true, false);

                    return Seq(WaitMs(MsToWaitForSearchResultsToReturn),
                               Act([=]() { m_messageBus.Publish(SearchMenu::OpenSearchMenuMessage(true)); }),
                               WaitMs(MsToWaitForSearchMenuToOpen));
                },

                [this]() {
                    static const std::string LightThemesManifestUrlDefault  = "http://d2xvsc8j92rfya.cloudfront.net/mobile-themes-new/v883/ambientwhite/manifest.bin.gz";
                    const long long MsToWaitForThemeToLoad = 3000;
                    const PlaceJumps::View::PlaceJumpModel SanFran(
                            "SanFran",
                            Eegeo::Space::LatLong::FromDegrees(37.743676, -122.451021),
                            0.0f,
                            3000.0f,
                            "");

                    m_messageBus.Publish(SearchMenu::OpenSearchMenuMessage(false));
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_placeJumpController.JumpTo(SanFran);
                    m_flattenButtonModel.Unflatten();
                    m_cityThemeLoader.LoadThemes(LightThemesManifestUrlDefault, "Summer", "DayDefault");

                    return Seq(WaitForStreaming(&m_cityThemeLoader),
                               WaitMs(MsToWaitForThemeToLoad));
                },

                [this]() {
                    static const std::string SciFiThemesManifestUrlDefault = "http://d2xvsc8j92rfya.cloudfront.net/mobile-themes-new/v883/scifi/manifest.bin.gz";
                    const long long MsToWaitForSearchResultsToClearAndThemeToLoad = 3000;
                    const PlaceJumps::View::PlaceJumpModel LA(
                            "LA",
                            Eegeo::Space::LatLong::FromDegrees(34.052074, -118.260257),
                            160.0f,
                            1000.0f,
                            "");

                    m_placeJumpController.JumpTo(LA);
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_cityThemeLoader.LoadThemes(SciFiThemesManifestUrlDefault, "Summer", "DayDefault");

                    return Seq(WaitForStreaming(&m_cityThemeLoader),
                               WaitMs(MsToWaitForSearchResultsToClearAndThemeToLoad));
                }
            }};
        }

        const unsigned long AutomatedScreenshotController::NumScenes() const
        {
            return States().size();
        }

        std::function<bool()> AutomatedScreenshotController::SetupState(const unsigned long state)
        {
            return States()[state]();
        }

        bool AutomatedScreenshotController::Done() const
        {
            return m_sceneIndex == NumScenes();
        }

        void AutomatedScreenshotController::Update(const float dt)
        {
            switch (m_execState)
            {
            case ExecStateStreamingInitialSceneAndManifest:
                if (!m_eegeoWorld.IsStreaming(false))
                {
                    NextScene();
                    m_execState = ExecStateWaitingForSceneToStream;
                    m_updateCyclesToWait = UpdateCyclesToWaitForSplashScreenToDisappear;
                }
                return;

            case ExecStateWaitingForSceneToStream:
                if (!m_eegeoWorld.IsStreaming(false))
                {
                    m_execState = ExecStateWaitForSceneToRender;
                }
                return;

            case ExecStateWaitForSceneToRender:
                if (m_updateCyclesToWait <= 0 && m_waitPredicate())
                {
                    m_screenshotService.screenshot("screenshot");
                    m_execState = ExecStatePrepareNextScene;
                }

                m_updateCyclesToWait--;
                return;

            case ExecStatePrepareNextScene:
                if (Done())
                {
                    m_completedScreenshotsCallbacks.ExecuteCallbacks();
                    m_execState = ExecStateDone;
                }
                else
                {
                    NextScene();
                    m_updateCyclesToWait = UpdateCyclesPerScreenshot;
                    m_execState = ExecStateWaitingForSceneToStream;
                }
                return;

            case ExecStateDone:
            default:
                return;
            }
        }

        void AutomatedScreenshotController::InsertCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_completedScreenshotsCallbacks.AddCallback(callback);
        }

        void AutomatedScreenshotController::RemoveCompletedScreenshotsCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_completedScreenshotsCallbacks.RemoveCallback(callback);
        }
    }
}
