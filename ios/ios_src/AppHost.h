// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
#include "WorldPinOnMapViewIncludes.h"
#include "CompassViewIncludes.h"
#include "AboutPageViewIncludes.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "BidirectionalBus.h"
#include "MyPinDetailsViewIncludes.h"
#include "iOSConnectivityService.h"
#include "OptionsViewIncludes.h"
#include "NetIncludes.h"

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : protected Eegeo::NonCopyable
{
public:
    AppHost(
        ViewController& viewController,
        UIView* pView,
        Eegeo::Rendering::ScreenProperties screenProperties
    );
    ~AppHost();

    bool IsRunning();

    void Update(float dt);
    void Draw(float dt);

    void OnPause();
    void OnResume();

    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

private:
    UIView* m_pView;
    ViewController& m_viewController;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
    Eegeo::iOS::iOSLocationService* m_piOSLocationService;
    Eegeo::iOS::iOSConnectivityService* m_piOSConnectivityService;
    AppInputDelegate* m_pAppInputDelegate;
    AppLocationDelegate* m_pAppLocationDelegate;

    Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory m_iOSInputBoxFactory;
    Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory m_iOSKeyboardInputFactory;
    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory m_iOSAlertBoxFactory;
    Eegeo::UI::NativeUIFactories m_iOSNativeUIFactories;
    Eegeo::iOS::iOSPlatformAbstractionModule* m_piOSPlatformAbstractionModule;

    ExampleApp::PrimaryMenu::View::IPrimaryMenuViewModule* m_pPrimaryMenuViewModule;
    ExampleApp::SecondaryMenu::View::ISecondaryMenuViewModule* m_pSecondaryMenuViewModule;
    ExampleApp::SearchResultMenu::View::ISearchResultMenuViewModule* m_pSearchResultMenuViewModule;
    ExampleApp::ModalBackground::View::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::View::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::WorldPins::View::IWorldPinOnMapViewModule* m_pWorldPinOnMapViewModule;
    ExampleApp::Compass::View::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;
    ExampleApp::PersistentSettings::iOSPersistentSettingsModel m_iOSPersistentSettingsModel;
    ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule* m_pInitialExperienceModule;
    ExampleApp::AboutPage::View::IAboutPageViewModule* m_pAboutPageViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationInitiationViewModule* m_pMyPinCreationInitiationViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationConfirmationViewModule* m_pMyPinCreationConfirmationViewModule;
    ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModule* m_pMyPinCreationDetailsViewModule;
    ExampleApp::MyPinDetails::View::IMyPinDetailsViewModule* m_pMyPinDetailsViewModule;
    ExampleApp::Options::View::IOptionsViewModule* m_pOptionsViewModule;
    ExampleApp::Net::SdkModel::INetworkCapabilities* m_pNetworkCapabilities;

    ExampleApp::MobileExampleApp* m_pApp;
    bool m_requestedApplicationInitialiseViewState;

    ExampleApp::ExampleAppMessaging::TMessageBus m_messageBus;

    void CreateApplicationViewModules(const Eegeo::Rendering::ScreenProperties& screenProperties);
    void DestroyApplicationViewModules();
};

