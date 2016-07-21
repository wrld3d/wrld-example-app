// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Graphics.h"
#include "WindowsFileIO.h"
#include "WindowsCacheFileIO.h"
#include "WindowsTextureFileLoader.h"
#include "WindowsInputProcessor.h"
#include "WindowsLocationService.h"
#include "IJpegLoader.h"
#include "WindowsUrlEncoder.h"
#include "GlobeCameraInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "WindowsInputHandler.h"
#include "WindowsInputBoxFactory.h"
#include "WindowsKeyboardInputFactory.h"
#include "WindowsAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightRepository.h"
#include "GlobalShadowing.h"
#include "Blitter.h"
#include "WindowsNativeState.h"
#include "AppInputDelegate.h"
#include "Modules.h"
#include "InitialExperience.h"
#include "WindowsPersistentSettings.h"
#include "ViewControllerUpdater.h"
#include "MenuViewIncludes.h"
#include "ModalBackgroundViewIncludes.h"
#include "FlattenButtonViewIncludes.h"
#include "SearchResultPoiViewIncludes.h"
#include "WorldPinOnMapViewIncludes.h"
#include "CompassViewIncludes.h"
#include "AboutPageViewIncludes.h"
#include "MyPinCreationViewIncludes.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "MyPinDetailsViewIncludes.h"
#include "BidirectionalBus.h"
#include "WindowsConnectivityService.h"
#include "InitialExperienceViewIncludes.h"
#include "OptionsViewIncludes.h"
#include "WatermarkViewIncludes.h"
#include "NetIncludes.h"
#include "Search.h"
#include "SdkModelDomainEventBus.h"
#include "IEegeoErrorHandler.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "WindowsFlurryMetricsService.h"
#include "Interiors.h"
#include "InteriorsExplorerViewIncludes.h"
#include "SettingsMenuModule.h"
#include "SearchMenuModule.h"
#include "ISearchResultSectionViewModule.h"
#include "ISurveyViewModule.h"
#include "IMenuReactionModel.h"

class AppHost : public Eegeo::IEegeoErrorHandler, protected Eegeo::NonCopyable
{
public:
    AppHost(
        WindowsNativeState& nativeState,
        Eegeo::Rendering::ScreenProperties screenProperties,
        EGLDisplay display,
        EGLSurface shareSurface,
        EGLContext resourceBuildShareContext,
        bool hasNativeTouchInput,
        int maxDeviceTouchCount
        );
    ~AppHost();

    void Update(float dt);
    void Draw(float dt);

    void CreateUiFromUiThread();
    void RevealUiFromUiThread();
    void UpdateUiViewsFromUiThread(float deltaSeconds);
    void DestroyUiFromUiThread();
    void HandleApplicationUiCreatedOnNativeThread();

    void OnPause();
    void OnResume();

    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

    void HandleFailureToProvideWorkingApiKey();

    void HandleFailureToDownloadBootstrapResources();
    void HandleNoConnectivityWarning();
    void HandleInvalidConnectivityError();

    void HandleMouseInputEvent(const Eegeo::Windows::Input::MouseInputEvent& event);
    void HandleKeyboardInputEvent(const Eegeo::Windows::Input::KeyboardInputEvent& event);
    void HandleTouchScreenInputEvent(const Eegeo::Windows::Input::TouchScreenInputEvent& event);

    void SetAllInputEventsToPointerUp(int x, int y);
    void SetAllTouchInputEventsToPointerUp(int touchId);

    void SetEnvironmentFlatten(bool flattenState);
    void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
    void SendCameraLocationToGUI();

    void SetSharedSurface(EGLSurface sharedSurface);
    void SetViewportOffset(float x, float y);

    bool ShouldStartFullscreen();

private:
    bool m_isPaused;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
    Eegeo::Windows::WindowsLocationService* m_pWindowsLocationService;

    bool m_shouldStartFullscreen;

    WindowsNativeState& m_nativeState;
    AppInputDelegate* m_pAppInputDelegate;

    Eegeo::Windows::Input::WindowsInputHandler m_inputHandler;
    Eegeo::UI::NativeInput::Windows::WindowsInputBoxFactory m_WindowsInputBoxFactory;
    Eegeo::UI::NativeInput::Windows::WindowsKeyboardInputFactory m_WindowsKeyboardInputFactory;
    Eegeo::UI::NativeAlerts::Windows::WindowsAlertBoxFactory m_WindowsAlertBoxFactory;
    Eegeo::UI::NativeUIFactories m_WindowsNativeUIFactories;

    Eegeo::Windows::Input::WindowsInputProcessor* m_pInputProcessor;

    ExampleApp::ModalBackground::SdkModel::IModalBackgroundNativeViewModule* m_pModalBackgroundNativeViewModule;


    Eegeo::Windows::WindowsPlatformAbstractionModule* m_pWindowsPlatformAbstractionModule;
    ExampleApp::Menu::View::IMenuViewModule* m_pSettingsMenuViewModule;
    ExampleApp::Menu::View::IMenuViewModule* m_pSearchMenuViewModule;
    ExampleApp::ModalBackground::View::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::View::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::SearchResultSection::View::ISearchResultSectionViewModule* m_pSearchResultSectionViewModule;
    ExampleApp::WorldPins::View::IWorldPinOnMapViewModule* m_pWorldPinOnMapViewModule;
    ExampleApp::AboutPage::View::IAboutPageViewModule* m_pAboutPageViewModule;
    ExampleApp::Compass::View::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationViewModule* m_pMyPinCreationViewModule;
    ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModule* m_pMyPinCreationDetailsViewModule;
    ExampleApp::MyPinDetails::View::IMyPinDetailsViewModule* m_pMyPinDetailsViewModule;
    ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule* m_pInitialExperienceIntroViewModule; // TODO: Interface.
    ExampleApp::Surveys::View::ISurveyViewModule* m_pSurverysViewModule;
    ExampleApp::Options::View::IOptionsViewModule* m_pOptionsViewModule;
    ExampleApp::Watermark::View::IWatermarkViewModule* m_pWatermarkViewModule;
    ExampleApp::Net::SdkModel::INetworkCapabilities* m_pNetworkCapabilities;
    ExampleApp::Metrics::WindowsFlurryMetricsService* m_pWindowsFlurryMetricsService;
	ExampleApp::InteriorsExplorer::View::IInteriorsExplorerViewModule* m_pInteriorsExplorerViewModule;
    ExampleApp::Menu::View::IMenuReactionModel* m_pMenuReaction;

    ExampleApp::MobileExampleApp* m_pApp;

    ExampleApp::PersistentSettings::WindowsPersistentSettingsModel* m_pWindowsPersistentSettingsModel;
    ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule* m_pInitialExperienceModule;

    bool m_createdUIModules;
    bool m_requestedApplicationInitialiseViewState;
    bool m_uiCreatedMessageReceivedOnNativeThread;
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;

    ExampleApp::ExampleAppMessaging::TMessageBus m_messageBus;
    ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus m_sdkDomainEventBus;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<AppHost> m_failAlertHandler;

    void DispatchRevealUiMessageToUiThreadFromNativeThread();
    void DispatchUiCreatedMessageToNativeThreadFromUiThread();
    void CreateApplicationViewModulesFromUiThread();
    void DestroyApplicationViewModulesFromUiThread();

    void HandleStartupFailure();

    int m_maxDeviceTouchCount;
};