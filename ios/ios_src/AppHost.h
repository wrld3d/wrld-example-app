// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Graphics.h"
#include "IJpegLoader.h"
#include "GlobeCameraInterestPointProvider.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TouchEventWrapper.h"
#include "Blitter.h"
#include "AppInputDelegate.h"
#include "AppLocationDelegate.h"
#include "Modules.h"
#include "MobileExampleApp.h"
#include "InitialExperience.h"
#include "iOSPersistentSettingsModel.h"
#include "ViewControllerUpdater.h"
#include "PrimaryMenuViewIncludes.h"
#include "SecondaryMenuViewIncludes.h"
#include "SearchResultMenuViewModule.h"
#include "ModalBackgroundViewIncludes.h"
#include "FlattenButtonViewIncludes.h"
#include "SearchResultPoiViewIncludes.h"
#include "SearchResultOnMapViewIncludes.h"
#include "CompassViewIncludes.h"
#include "AboutPageViewIncludes.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : protected Eegeo::NonCopyable
{
public:
	AppHost(
            ViewController& viewController,
            UIView* pView,
            float displayWidth,
            float displayHeight,
            float deviceDpi,
            float pixelScale
            );
	~AppHost();
    
    bool IsRunning();
    
	void Update(float dt);
	void Draw(float dt);
    
	void OnPause();
	void OnResume();
    
	void SetViewportOffset(float x, float y);
    
private:
    UIView* m_pView;
    ViewController& m_viewController;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
    Eegeo::Rendering::ScreenProperties* m_pScreenProperties;
	Eegeo::iOS::iOSLocationService* m_piOSLocationService;
	AppInputDelegate* m_pAppInputDelegate;
    AppLocationDelegate* m_pAppLocationDelegate;
    
	Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory m_iOSInputBoxFactory;
	Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory m_iOSKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory m_iOSAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_iOSNativeUIFactories;
    Eegeo::iOS::iOSPlatformAbstractionModule* m_piOSPlatformAbstractionModule;
    
    ExampleApp::PrimaryMenu::IPrimaryMenuViewModule* m_pPrimaryMenuViewModule;
    ExampleApp::SecondaryMenu::ISecondaryMenuViewModule* m_pSecondaryMenuViewModule;
    ExampleApp::SearchResultMenu::ISearchResultMenuViewModule* m_pSearchResultMenuViewModule;
    ExampleApp::ModalBackground::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::SearchResultOnMap::ISearchResultOnMapViewModule* m_pSearchResultOnMapViewModule;
    ExampleApp::Compass::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::ViewControllerUpdater::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;
    ExampleApp::PersistentSettings::iOSPersistentSettingsModel m_iOSPersistentSettingsModel;
    ExampleApp::InitialExperience::IInitialExperienceModule* m_pInitialExperienceModule;
    ExampleApp::AboutPage::IAboutPageViewModule* m_pAboutPageViewModule;
    
    ExampleApp::MobileExampleApp* m_pApp;
    bool m_requestedApplicationInitialiseViewState;
    
    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus m_uiToNativeMessageBus;
    ExampleApp::ExampleAppMessaging::NativeToUiMessageBus m_nativeToUiMessageBus;
    
    void CreateApplicationViewModules();
    void DestroyApplicationViewModules();
};

