// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    class MobileExampleApp;
}

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Graphics.h"
#include "WindowsFileIO.h"
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
#include "WindowsNativeState.h"
#include "AppInputDelegate.h"
#include "Modules.h"
#include "InitialExperience.h"
#include "WindowsPersistentSettingsModel.h"
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
#include "ICallback.h"
#include "UserInteraction.h"
#include "IMenuReactionModel.h"
#include "AppWiring.h"
#include "IViewControllerUpdaterModel.h"
#include "WebConnectivityValidator.h"

class AppHost : protected Eegeo::NonCopyable
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

    void NotifyScreenPropertiesChanged(const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties);

    void HandleFailureToProvideWorkingApiKey();

    void HandleFailureToDownloadBootstrapResources();

    void HandleMouseInputEvent(const Eegeo::Windows::Input::MouseInputEvent& event);
    void HandleKeyboardInputEvent(const Eegeo::Windows::Input::KeyboardInputEvent& event);
    void HandleTouchScreenInputEvent(const Eegeo::Windows::Input::TouchScreenInputEvent& event);
    void SetAllInputEventsToPointerUp(int x, int y);
    void SetTouchInputEventToPointerUp(int touchId);
    void PopAllTouchEvents();

    void SetEnvironmentFlatten(bool flattenState);
    void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
    void SendCameraLocationToGUI();

    bool ShouldStartFullscreen();

    void SetSharedSurface(EGLSurface sharedSurface);
    void SetViewportOffset(float x, float y);

    template <class T>
    void AddViewControllerUpdatable()
    {
        auto t = m_wiring->Resolve<T>();
        auto controller = m_wiring->Resolve<ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel>();
        Eegeo_ASSERT(t != nullptr);
        Eegeo_ASSERT(controller != nullptr);
        controller->AddUpdateableObject(*t);
    }

private:
    Eegeo::Helpers::TCallback0<AppHost> m_loadingScreenCallback;
    void OnLoadingScreenComplete();

    ExampleApp::ExampleAppMessaging::TMessageBus& GetMessageBus();

    bool m_isPaused;
    WindowsNativeState& m_nativeState;
    std::shared_ptr<AppInputDelegate> m_appInputDelegate;
    std::shared_ptr<ExampleApp::AppWiring> m_wiring;
    std::shared_ptr<ExampleApp::MobileExampleApp> m_app;
    std::shared_ptr<Eegeo::Web::WebConnectivityValidator> m_connectivityValidator;
    std::shared_ptr<ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel> m_viewControllerUpdater;
    std::shared_ptr<ExampleApp::ExampleAppMessaging::TMessageBus> m_messageBus;
    std::shared_ptr<Eegeo::Location::ILocationService> m_locationService;
    std::shared_ptr<Eegeo::Windows::WindowsPlatformAbstractionModule> m_windowsAbstractionModule;
    std::shared_ptr<ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeView> m_modalBackground;

    bool m_registeredUIModules;
    bool m_resolvedUIModules;
    bool m_uiCreatedMessageReceivedOnNativeThread;

    void DispatchRevealUiMessageToUiThreadFromNativeThread();
    void DispatchUiCreatedMessageToNativeThreadFromUiThread();
    void CreateApplicationViewModulesFromUiThread();
    void DestroyApplicationViewModulesFromUiThread();

    void PublishNetworkConnectivityStateToUIThread();
};