// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

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
#include "IInteriorsExplorerViewModule.h"
#include "SearchResultSectionViewIncludes.h"
#include "IMenuReactionModel.h"
#include "TagSearchViewIncludes.h"
#include "AlwaysActiveUserIdleService.h"

class AppHost : public Eegeo::IEegeoErrorHandler, protected Eegeo::NonCopyable
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

    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

    void HandleFailureToProvideWorkingApiKey();

    void HandleFailureToDownloadBootstrapResources();

    void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

    void HandleOpenUrlEvent(const AppInterface::UrlData& data);

    void SetEnvironmentFlatten(bool flattenState);
    void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
    void SendCameraLocationToGUI();

    void SetSharedSurface(EGLSurface sharedSurface);
    void SetViewportOffset(float x, float y);

private:
    bool m_isPaused;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
    Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
    Eegeo::Android::AndroidConnectivityService* m_pAndroidConnectivityService;

    AndroidNativeState& m_nativeState;
    AppInputDelegate* m_pAppInputDelegate;

    Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
    Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
    Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
    Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
    Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

    Eegeo::Android::Input::AndroidInputProcessor* m_pInputProcessor;

    ExampleApp::ModalBackground::SdkModel::IModalBackgroundNativeViewModule* m_pModalBackgroundNativeViewModule;


    Eegeo::Android::AndroidPlatformAbstractionModule* m_pAndroidPlatformAbstractionModule;
    ExampleApp::Menu::View::IMenuViewModule* m_pSettingsMenuViewModule;
    ExampleApp::Menu::View::IMenuViewModule* m_pSearchMenuViewModule;
    ExampleApp::SearchResultSection::View::ISearchResultSectionViewModule* m_pSearchResultSectionViewModule;
    ExampleApp::TagSearch::View::ITagSearchViewModule* m_pTagSearchViewModule;
    ExampleApp::ModalBackground::View::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::View::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::AboutPage::View::IAboutPageViewModule* m_pAboutPageViewModule;
    ExampleApp::Compass::View::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationViewModule* m_pMyPinCreationViewModule;
    ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModule* m_pMyPinCreationDetailsViewModule;
    ExampleApp::MyPinDetails::View::IMyPinDetailsViewModule* m_pMyPinDetailsViewModule;
    ExampleApp::InteriorsExplorer::View::IInteriorsExplorerViewModule* m_pInteriorsExplorerViewModule;
    ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule* m_pInitialExperienceIntroViewModule; // TODO: Interface.
    ExampleApp::Options::View::IOptionsViewModule* m_pOptionsViewModule;
    ExampleApp::Watermark::View::IWatermarkViewModule* m_pWatermarkViewModule;
    ExampleApp::Net::SdkModel::INetworkCapabilities* m_pNetworkCapabilities;
    ExampleApp::Metrics::AndroidFlurryMetricsService* m_pAndroidFlurryMetricsService;

    ExampleApp::Menu::View::IMenuReactionModel* m_pMenuReactionModel;

    ExampleApp::MobileExampleApp* m_pApp;

    ExampleApp::PersistentSettings::AndroidPersistentSettingsModel m_androidPersistentSettingsModel;
    ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule* m_pInitialExperienceModule;

    bool m_createdUIModules;
    bool m_requestedApplicationInitialiseViewState;
    bool m_uiCreatedMessageReceivedOnNativeThread;
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;

    ExampleApp::ExampleAppMessaging::TMessageBus m_messageBus;
    ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus m_sdkDomainEventBus;
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<AppHost> m_failAlertHandler;
    Eegeo::Helpers::TCallback1<AppHost, const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage&> m_userInteractionEnabledChangedHandler;

    Eegeo::Input::AlwaysActiveUserIdleService m_userIdleService;

    void DispatchRevealUiMessageToUiThreadFromNativeThread();
    void DispatchUiCreatedMessageToNativeThreadFromUiThread();
    void CreateApplicationViewModulesFromUiThread();
    void DestroyApplicationViewModulesFromUiThread();

    void SetTouchExclusivity();

    void HandleStartupFailure();
    void HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message);
    void HandleNoConnectivityWarning();
    void HandleInvalidConnectivityError();

    void PublishNetworkConnectivityStateToUIThread();
};
