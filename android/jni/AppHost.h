// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Graphics.h"
#include "AndroidFileIO.h"
#include "AndroidCacheFileIO.h"
#include "AndroidHttpCache.h"
#include "AndroidTextureFileLoader.h"
#include "AndroidWebRequestService.hpp"
#include "AndroidWebLoadRequestFactory.h"
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
#include "Blitter.h"
#include "AndroidNativeState.h"
#include "AppInputDelegate.h"
#include "Modules.h"
#include <vector>
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
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

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

	void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

	void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

	void SetEnvironmentFlatten(bool flattenState);
	void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
	void SendCameraLocationToGUI();

	void SetSharedSurface(EGLSurface sharedSurface);
	void SetViewportOffset(float x, float y);

private:
	bool m_isPaused;
	Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
	Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
	AndroidNativeState& m_nativeState;
	AppInputDelegate* m_pAppInputDelegate;

	Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
	Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
	Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

	Eegeo::Android::Input::AndroidInputProcessor* m_pInputProcessor;

	ExampleApp::ModalBackground::IModalBackgroundNativeViewModule* m_pModalBackgroundNativeViewModule;


	Eegeo::Android::AndroidPlatformAbstractionModule* m_pAndroidPlatformAbstractionModule;
	ExampleApp::Menu::IMenuViewModule* m_pPrimaryMenuViewModule;
	ExampleApp::Menu::IMenuViewModule* m_pSecondaryMenuViewModule;
	ExampleApp::Menu::IMenuViewModule* m_pSearchResultMenuViewModule;
	ExampleApp::ModalBackground::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
	ExampleApp::FlattenButton::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
	ExampleApp::SearchResultPoi::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
	ExampleApp::WorldPins::IWorldPinOnMapViewModule* m_pWorldPinOnMapViewModule;
	ExampleApp::AboutPage::IAboutPageViewModule* m_pAboutPageViewModule;
	ExampleApp::Compass::ICompassViewModule* m_pCompassViewModule;
	ExampleApp::MyPinCreation::IMyPinCreationViewModule* m_pMyPinCreationViewModule;
    ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModule* m_pMyPinCreationDetailsViewModule;
    ExampleApp::MyPinDetails::IMyPinDetailsViewModule* m_pMyPinDetailsViewModule;

	ExampleApp::MobileExampleApp* m_pApp;

	ExampleApp::PersistentSettings::AndroidPersistentSettingsModel m_androidPersistentSettingsModel;
	ExampleApp::InitialExperience::IInitialExperienceModule* m_pInitialExperienceModule;

	bool m_createdUIModules;
	bool m_requestedApplicationInitialiseViewState;
	bool m_uiCreatedMessageReceivedOnNativeThread;
	ExampleApp::ViewControllerUpdater::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;

	ExampleApp::ExampleAppMessaging::UiToNativeMessageBus m_uiToNativeMessageBus;
	ExampleApp::ExampleAppMessaging::NativeToUiMessageBus m_nativeToUiMessageBus;

	void DispatchRevealUiMessageToUiThreadFromNativeThread();
	void DispatchUiCreatedMessageToNativeThreadFromUiThread();
	void CreateApplicationViewModulesFromUiThread();
	void DestroyApplicationViewModulesFromUiThread();
};


