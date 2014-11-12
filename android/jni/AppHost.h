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
#include "SearchResultOnMapViewIncludes.h"
#include "CompassViewIncludes.h"
#include "AboutPageViewIncludes.h"
#include "PoiCreationViewIncludes.h"
#include "PoiCreationDetailsViewIncludes.h"

class AppHost : protected Eegeo::NonCopyable
{
public:
	AppHost(
	    AndroidNativeState& nativeState,
	    float displayWidth,
	    float displayHeight,
	    EGLDisplay display,
	    EGLSurface shareSurface,
	    EGLContext resourceBuildShareContext
	);
	~AppHost();

	void Update(float dt);
	void Draw(float dt);

	void OnPause();
	void OnResume();

	void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

	void SetEnvironmentFlatten(bool flattenState);
	void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
	void SendCameraLocationToGUI();

	void SetSharedSurface(EGLSurface sharedSurface);
	void SetViewportOffset(float x, float y);

private:
	bool m_isPaused;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
	Eegeo::Rendering::ScreenProperties* m_pScreenProperties;
	Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
	AndroidNativeState& m_nativeState;
	AppInputDelegate* m_pAppInputDelegate;

	Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
	Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
	Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

	Eegeo::Android::Input::AndroidInputProcessor* m_pInputProcessor;

	Eegeo::Android::AndroidPlatformAbstractionModule* m_pAndroidPlatformAbstractionModule;
	ExampleApp::ViewControllerUpdater::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;
    ExampleApp::Menu::IMenuViewModule* m_pPrimaryMenuViewModule;
    ExampleApp::Menu::IMenuViewModule* m_pSecondaryMenuViewModule;
    ExampleApp::Menu::IMenuViewModule* m_pSearchResultMenuViewModule;
    ExampleApp::ModalBackground::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::SearchResultOnMap::ISearchResultOnMapViewModule* m_pSearchResultOnMapViewModule;
    ExampleApp::AboutPage::IAboutPageViewModule* m_pAboutPageViewModule;
    ExampleApp::Compass::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::PoiCreation::IPoiCreationViewModule* m_pPoiCreationViewModule;
    ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModule* m_pPoiCreationDetailsViewModule;

    ExampleApp::MobileExampleApp* m_pApp;

    ExampleApp::PersistentSettings::AndroidPersistentSettingsModel m_androidPersistentSettingsModel;
    ExampleApp::InitialExperience::IInitialExperienceModule* m_pInitialExperienceModule;

    void CreateApplicationViewModules();
    void DestroyApplicationViewModules();
};

