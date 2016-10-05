// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
	class AppWiring;
	class MobileExampleApp;
}

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Graphics.h"
#include "AndroidFileIO.h"
#include "AndroidTextureFileLoader.h"
#include "AndroidInputProcessor.h"
#include "AndroidLocationService.h"
#include "IJpegLoader.h"
#include "AndroidUrlEncoder.h"
#include "GlobeCameraInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "AndroidInputHandler.h"
#include "AndroidInputBoxFactory.h"
#include "AndroidKeyboardInputFactory.h"
#include "AndroidAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightRepository.h"
#include "GlobalShadowing.h"
#include "TouchEventWrapper.h"
#include "AndroidNativeState.h"
#include "AppInputDelegate.h"
#include "Modules.h"
#include "InitialExperience.h"
#include "AndroidPersistentSettingsModel.h"
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
#include "AndroidConnectivityService.h"
#include "InitialExperienceViewIncludes.h"
#include "OptionsViewIncludes.h"
#include "WatermarkViewIncludes.h"
#include "NetIncludes.h"
#include "Search.h"
#include "SdkModelDomainEventBus.h"
#include "IEegeoErrorHandler.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "AndroidFlurryMetricsService.h"
#include "ICallback.h"
#include "UserInteraction.h"
#include "IMenuReactionModel.h"
#include <atomic>

class AppHost : protected Eegeo::NonCopyable
{
public:
    AppHost(
        AndroidNativeState& nativeState,
        Eegeo::Rendering::ScreenProperties screenProperties,
        EGLDisplay display,
        EGLSurface shareSurface,
        EGLContext resourceBuildShareContext
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

    void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

    void SetEnvironmentFlatten(bool flattenState);
    void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
    void SendCameraLocationToGUI();

    void SetSharedSurface(EGLSurface sharedSurface);
    void SetViewportOffset(float x, float y);

private:
    ExampleApp::ExampleAppMessaging::TMessageBus& GetMessageBus();

    bool m_isPaused;
    AndroidNativeState& m_nativeState;
    AppInputDelegate* m_pAppInputDelegate;

    Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
    Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
    Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
    Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
    Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

    std::shared_ptr<ExampleApp::AppWiring> m_wiring;
    std::shared_ptr<ExampleApp::MobileExampleApp> m_app;

    bool m_registeredUIModules;
    bool m_resolvedUIModules;
    bool m_resolvedNativeTypes;
    std::atomic<bool> m_reoslvedNativeModules;
    bool m_requestedApplicationInitialiseViewState;
    bool m_uiCreatedMessageReceivedOnNativeThread;

    ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus m_sdkDomainEventBus;
    Eegeo::Helpers::TCallback1<AppHost, const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage&> m_userInteractionEnabledChangedHandler;

    void DispatchRevealUiMessageToUiThreadFromNativeThread();
    void DispatchUiCreatedMessageToNativeThreadFromUiThread();
    void CreateApplicationViewModulesFromUiThread();
    void DestroyApplicationViewModulesFromUiThread();

    void SetTouchExclusivity();

    void HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message);

    void PublishNetworkConnectivityStateToUIThread();
};
