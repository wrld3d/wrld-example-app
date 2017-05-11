// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <array>
#include <functional>

#include "ApplicationConfig.h"
#include "AutomatedScreenshotController.h"
#include "CameraTransitionService.h"
#include "CityThemeLoader.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ICallback.h"
#include "ICityThemesService.h"
#include "ICityThemesUpdater.h"
#include "IFlattenButtonModel.h"
#include "IMenuSectionViewModel.h"
#include "InteriorsCameraController.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"
#include "IPlaceJumpController.h"
#include "IScreenshotService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultPoiViewModel.h"
#include "IWeatherController.h"
#include "OpenSearchMenuMessage.h"
#include "OpenSearchMenuSectionMessage.h"
#include "PlaneSimulation.h"
#include "StreamingController.h"
#include "TimeHelpers.h"
#include "AppCameraController.h"
#include "SelectMenuItemMessage.h"
#include "WorldPinsModule.h"
#include "WorldPinsService.h"
#include "ClosePoiMessage.h"

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
                long long currentMillis = 0;
                return [=]() mutable {
                    if (currentMillis == 0)
                    {
                        currentMillis = Eegeo::Helpers::Time::MillisecondsSinceEpoch();
                    }
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

            const AutomatedScreenshotController::WaitPredicate WaitForCameraTransition(ExampleApp::CameraTransitions::SdkModel::CameraTransitionService* cameraTransitionService)
            {
                return [=]() { return !cameraTransitionService->IsTransitioning(); };
            }

            bool IsLandscapeLayout(Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                return screenProperties.GetScreenWidth() > screenProperties.GetScreenHeight();
            }
        }

        AutomatedScreenshotController::AutomatedScreenshotController(const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                                     CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService,
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
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     AppCamera::SdkModel::IAppCameraModule& appCameraModule,
                                                                     Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                     ExampleApp::WorldPins::SdkModel::IWorldPinsModule& worldPinsModule)
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
        , m_cityThemeLoader(eegeoWorld.GetCityThemesModule().GetCityThemeLoader())
        , m_cityThemesService(eegeoWorld.GetCityThemesModule().GetCityThemesService())
        , m_cityThemesUpdater(eegeoWorld.GetCityThemesModule().GetCityThemesUpdater())
        , m_messageBus(messageBus)
        , m_screenProperties(screenProperties)
        , m_worldPinsModule(worldPinsModule)
        , m_cameraTransitionService(cameraTransitionService)
        {
            m_planeSimulation.SetEnabled(false);
        }

        bool AutomatedScreenshotController::NextScene()
        {
            if (m_sceneIndex < AutomatedScreenshotController::NumScenes)
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

        AutomatedScreenshotController::WaitPredicate AutomatedScreenshotController::SharedLandmarkSceneWaitPredicate(const bool openSearchMenu) const
        {
            const long long MsToWaitForWatermarkToSettle = 3000;
            const long long MsToWaitForSearchResultsToReturn = 3000;
            const long long MsToWaitForSearchMenuToOpen = 2000;

            return Seq(WaitMs(MsToWaitForWatermarkToSettle),
                       Act([=]() { m_messageBus.Publish(SearchMenu::OpenSearchMenuMessage(openSearchMenu)); }),
                       WaitMs(MsToWaitForSearchMenuToOpen),
                       Act([=]() {
                           if (openSearchMenu)
                           {
                               m_messageBus.Publish(OpenSearchMenuSectionMessage([=](const Menu::View::IMenuSectionViewModel& section) {
                                   return openSearchMenu && section.Name() == "Find";
                               }));
                           }
                           else
                           {
                               m_searchQueryPerformer.PerformSearchQuery("", true, false);
                           }
                       }),
                       WaitMs(MsToWaitForSearchResultsToReturn));
        }

        AutomatedScreenshotController::WaitPredicate AutomatedScreenshotController::TabletVASceneSetup(bool openSearchMenu) const
        {
            const PlaceJumps::View::PlaceJumpModel VA(
                    "V&A",
                    Eegeo::Space::LatLong::FromDegrees(51.496819, -0.171966),
                    14.6f,
                    953.6f,
                    "");

            m_placeJumpController.JumpTo(VA);

            return SharedLandmarkSceneWaitPredicate(openSearchMenu);
        }

        AutomatedScreenshotController::WaitPredicate AutomatedScreenshotController::PhoneNYCSceneSetup(bool openSearchMenu) const
        {
            static const std::string LightThemesManifestUrlDefault  = "http://d2xvsc8j92rfya.cloudfront.net/mobile-themes-new/v883/ambientwhite/manifest.bin.gz";
            const PlaceJumps::View::PlaceJumpModel NYC(
                    "NYC",
                    Eegeo::Space::LatLong::FromDegrees(40.746636, -73.985261),
                    169.1f,
                    1456.0f,
                    "");

            m_placeJumpController.JumpTo(NYC);
            m_cityThemeLoader.LoadThemes(LightThemesManifestUrlDefault, "Summer", "DayDefault");

            return SharedLandmarkSceneWaitPredicate(openSearchMenu);
        }

        AutomatedScreenshotController::WaitPredicate AutomatedScreenshotController::SelectedPinSceneSetup(const std::string& query, int searchMenuPinIx) const
        {
            const long long MsToWaitForSearchResults = 7000;
            const long long MsToWaitForCameraToTransitionToPoi = 5000;
            const long long MsWaitForPoiToOpen = 5000;

            m_searchQueryPerformer.PerformSearchQuery(query, false, false);
            return Seq(WaitMs(MsToWaitForSearchResults),
                       Act([=]() { m_messageBus.Publish(SelectMenuItemMessage(searchMenuPinIx)); }),
                       WaitMs(MsToWaitForCameraToTransitionToPoi),
                       Act([=]() { m_worldPinsModule.GetWorldPinsService().HandleTouchTap({Eegeo::v2(m_screenProperties.GetScreenWidth()/2, m_screenProperties.GetScreenHeight()/2)}); }),
                       WaitMs(MsWaitForPoiToOpen));
        }

        const std::array<AutomatedScreenshotController::SceneSetupFunction, AutomatedScreenshotController::NumScenes> AutomatedScreenshotController::States() const
        {
            return {{
                [this]() {
                    const PlaceJumps::View::PlaceJumpModel London(
                            "London",
                            Eegeo::Space::LatLong::FromDegrees(51.512179, -0.080664),
                            162.2f,
                            1780.1f,
                            "");

                    m_flattenButtonModel.Unflatten();
                    m_placeJumpController.JumpTo(London);
                    m_weatherController.SetTime("Day");
                    m_weatherController.SetTheme("Summer");

                    return WaitMs(8000);
                },

                [this]() {
                    const long long WaitMsForInteriorToLoad = 4000;
                    const long long MsToWaitForCameraToEnterInterior = 3000;
                    const Eegeo::Resources::Interiors::InteriorId WestportHouseInteriorId("westport_house");
                    const Eegeo::Space::LatLong location(Eegeo::Space::LatLong::FromDegrees(56.460108, -2.978094));
                    const float altitude = 388.7f;
                    const PlaceJumps::View::PlaceJumpModel WestportHouse(
                            "WestportHouse",
                            location,
                            312.8f,
                            altitude,
                            "");

                    m_placeJumpController.JumpTo(WestportHouse);

                    return Seq(WaitMs(WaitMsForInteriorToLoad),
                               Act([=]() { m_interiorSelectionModel.SelectInteriorId(WestportHouseInteriorId); }),
                               WaitMs(MsToWaitForCameraToEnterInterior),
                               Act([=]() {
                                   m_cameraTransitionService.StartTransitionTo(location.ToECEF(), altitude, WestportHouseInteriorId, 0, true);
                               }),
                               WaitForCameraTransition(&m_cameraTransitionService),
                               WaitMs(2000));
                },

                [this]() {
                    return IsLandscapeLayout(m_screenProperties)
                            ? TabletVASceneSetup(true)
                            : PhoneNYCSceneSetup(true);
                },

                [this]() {
                    return IsLandscapeLayout(m_screenProperties)
                           ? TabletVASceneSetup(false)
                           : PhoneNYCSceneSetup(false);
                },
                
                [this]() {
                    return IsLandscapeLayout(m_screenProperties)
                           ? SelectedPinSceneSetup("Victoria and Albert Museum", 2)
                           : SelectedPinSceneSetup("Empire State Building", 0);
                },

                [this]() {
                    static const std::string LightThemesManifestUrlDefault  = "http://d2xvsc8j92rfya.cloudfront.net/mobile-themes-new/v883/ambientwhite/manifest.bin.gz";
                    const long long MsToWaitForSearchQueryToClear = 3000;
                    const long long MsToWaitForThemeToLoad = 3000;
                    const PlaceJumps::View::PlaceJumpModel SanFran(
                            "SanFran",
                            Eegeo::Space::LatLong::FromDegrees(37.742448, -122.446477),
                            27.2f,
                            1914.3f,
                            "");
                    
                    m_messageBus.Publish(ClosePoiMessage());
                    m_messageBus.Publish(SearchMenu::OpenSearchMenuMessage(false));
                    m_placeJumpController.JumpTo(SanFran);
                    m_flattenButtonModel.Unflatten();
                    m_cityThemeLoader.LoadThemes(LightThemesManifestUrlDefault, "Summer", "DayDefault");

                    return Seq(WaitMs(MsToWaitForSearchQueryToClear),
                               Act([=]() {
                        m_searchQueryPerformer.RemoveSearchQueryResults(); }),
                               WaitForStreaming(&m_cityThemeLoader),
                               WaitMs(MsToWaitForThemeToLoad));
                },

                [this]() {
                    static const std::string SciFiThemesManifestUrlDefault = "http://d2xvsc8j92rfya.cloudfront.net/mobile-themes-new/v883/scifi/manifest.bin.gz";
                    const long long MsToWaitForSearchResultsToClearAndThemeToLoad = 3000;
                    const PlaceJumps::View::PlaceJumpModel LA(
                            "LA",
                            Eegeo::Space::LatLong::FromDegrees(34.051624, -118.254724),
                            187.6f,
                            1885.8f,
                            "");

                    m_placeJumpController.JumpTo(LA);
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_cityThemeLoader.LoadThemes(SciFiThemesManifestUrlDefault, "Summer", "DayDefault");

                    return Seq(WaitForStreaming(&m_cityThemeLoader),
                               WaitMs(MsToWaitForSearchResultsToClearAndThemeToLoad));
                }
            }};
        }

        std::function<bool()> AutomatedScreenshotController::SetupState(const unsigned long state)
        {
            return States()[state]();
        }

        bool AutomatedScreenshotController::Done() const
        {
            return m_sceneIndex == AutomatedScreenshotController::NumScenes;
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
