// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppHost.h"
#include "WindowsWebRequestService.hpp"
#include "WindowsSharedGlContext.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "RenderContext.h"
#include "GlobalLighting.h"
#include "GlobalFogging.h"
#include "AppInterface.h"
#include "JpegLoader.h"
#include "Blitter.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "WindowsThreadHelper.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "LoadingScreen.h"
#include "PlatformConfig.h"
#include "WindowsPlatformConfigBuilder.h"
#include "WindowsUrlEncoder.h"
#include "WindowsFileIO.h"
#include "WindowsLocationService.h"
#include "EegeoWorld.h"
#include "EnvironmentFlatteningService.h"
#include "TtyHandler.h"
#include "MenuViewModule.h"
#include "SecondaryMenuModule.h"
#include "ModalityModule.h"
#include "ModalBackgroundViewModule.h"
#include "ModalBackgroundNativeViewModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "SearchResultMenuModule.h"
#include "MenuOptionsModel.h"
#include "SearchModule.h"
#include "SearchResultOnMapModule.h"
#include "WorldPinsModule.h"
#include "RegularTexturePageLayout.h"
#include "PinsModule.h"
#include "SearchResultRepository.h"
#include "LatLongAltitude.h"
#include "SearchResultPoiModule.h"
#include "WindowsPlatformAbstractionModule.h"
#include "FlattenButtonModule.h"
#include "FlattenButtonViewModule.h"
#include "SearchResultPoiViewModule.h"
#include "WorldPinOnMapViewModule.h"
#include "PlaceJumpsModule.h"
#include "IPlaceJumpController.h"
#include "SecondaryMenuViewModule.h"
#include "SearchMenuViewModule.h"
#include "CompassViewModule.h"
#include "CompassModule.h"
#include "AboutPageViewModule.h"
#include "WindowsInitialExperienceModule.h"
#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"
#include "CategorySearchModule.h"
#include "ScreenProperties.h"
#include "MyPinCreationViewModule.h"
#include "IMyPinCreationModule.h"
#include "IMyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModule.h"
#include "MyPinDetailsViewModule.h"
#include "IMyPinDetailsModule.h"
#include "InitialExperienceIntroViewModule.h"
#include "Logger.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "SearchResultRepositoryObserver.h"
#include "IMyPinsModule.h"
#include "ApiKey.h"
#include "OptionsViewModule.h"
#include "OptionsView.h"
#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "NetworkCapabilities.h"
#include "WindowsYelpSearchServiceModule.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "SearchVendorNames.h"
#include "InteriorsExplorerViewModule.h"
#include "IInteriorsExplorerModule.h"
#include "WindowsPersistentSettingsModel.h"

using namespace Eegeo::Windows;
using namespace Eegeo::Windows::Input;

AppHost::AppHost(
    WindowsNativeState& nativeState,
    Eegeo::Rendering::ScreenProperties screenProperties,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
    )
    :m_isPaused(false)
    , m_pJpegLoader(NULL)
    , m_pWindowsLocationService(NULL)
    , m_pWindowsConnectivityService(NULL)
    , m_nativeState(nativeState)
    , m_WindowsInputBoxFactory(&nativeState)
    , m_WindowsKeyboardInputFactory(&nativeState, m_inputHandler)
    , m_WindowsAlertBoxFactory(&nativeState)
    , m_WindowsNativeUIFactories(m_WindowsAlertBoxFactory, m_WindowsInputBoxFactory, m_WindowsKeyboardInputFactory)
    , m_pInputProcessor(NULL)
    , m_pWindowsPlatformAbstractionModule(NULL)
    , m_pSecondaryMenuViewModule(NULL)
    , m_pSearchResultMenuViewModule(NULL)
    , m_pModalBackgroundViewModule(NULL)
    , m_pFlattenButtonViewModule(NULL)
    , m_pMyPinCreationViewModule(NULL)
    , m_pMyPinCreationDetailsViewModule(NULL)
    , m_pMyPinDetailsViewModule(NULL)
    , m_pSearchResultPoiViewModule(NULL)
    , m_pWorldPinOnMapViewModule(NULL)
    , m_pCompassViewModule(NULL)
    , m_pApp(NULL)
    , m_pWindowsPersistentSettingsModel(NULL)
    , m_createdUIModules(false)
    , m_requestedApplicationInitialiseViewState(false)
    , m_uiCreatedMessageReceivedOnNativeThread(false)
    , m_pViewControllerUpdaterModule(NULL)
    , m_pWindowsFlurryMetricsService(NULL)
    , m_pInitialExperienceIntroViewModule(NULL)
	, m_pInteriorsExplorerViewModule(NULL)
    , m_searchServiceModules()
    , m_failAlertHandler(this, &AppHost::HandleStartupFailure)
{
    ASSERT_NATIVE_THREAD
         
        Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

    Eegeo::TtyHandler::TtyEnabled = true;
    Eegeo::AssertHandler::BreakOnAssert = true;

    
    static LocationOverride locationOverride;
    locationOverride.latRadians = Eegeo::Math::Deg2Rad(51.5202688);
    locationOverride.lonRadians = Eegeo::Math::Deg2Rad(-0.0864312);
    locationOverride.altitudeMeters = 19.22;
    locationOverride.horizontalAccuracyMeters = 10.0;
    locationOverride.headingDegrees = 0.0;


    m_pWindowsLocationService = Eegeo_NEW(WindowsLocationService)(&nativeState, &locationOverride);
    m_pWindowsConnectivityService = Eegeo_NEW(WindowsConnectivityService)(&nativeState);

    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

    std::set<std::string> customApplicationAssetDirectories;
    customApplicationAssetDirectories.insert("SearchResultOnMap");
    customApplicationAssetDirectories.insert("ApplicationConfigs");

    m_pWindowsPlatformAbstractionModule = Eegeo_NEW(Eegeo::Windows::WindowsPlatformAbstractionModule)(
        nativeState,
        *m_pJpegLoader,
        display,
        resourceBuildShareContext,
        shareSurface,
        ExampleApp::ApiKey,
        customApplicationAssetDirectories);

    Eegeo::EffectHandler::Initialise();

    std::string deviceModel = nativeState.deviceModel;
    Eegeo::Config::PlatformConfig platformConfig = Eegeo::Windows::WindowsPlatformConfigBuilder(deviceModel).Build();
    platformConfig.OptionsConfig.InteriorsControlledByApp = true;

    m_pInputProcessor = Eegeo_NEW(Eegeo::Windows::Input::WindowsInputProcessor)(&m_inputHandler, m_nativeState.window, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

	m_pWindowsPersistentSettingsModel = Eegeo_NEW(ExampleApp::PersistentSettings::WindowsPersistentSettingsModel)(m_nativeState);

    m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::SdkModel::WindowsInitialExperienceModule)(
        m_nativeState,
        *m_pWindowsPersistentSettingsModel,
        m_messageBus
        );

    m_pNetworkCapabilities = Eegeo_NEW(ExampleApp::Net::SdkModel::NetworkCapabilities)(
        *m_pWindowsConnectivityService,
        m_pWindowsPlatformAbstractionModule->GetHttpCache(),
        *m_pWindowsPersistentSettingsModel);

    m_searchServiceModules[ExampleApp::Search::YelpVendorName] = Eegeo_NEW(ExampleApp::Search::Yelp::WindowsYelpSearchServiceModule)(
        nativeState,
        m_pWindowsPlatformAbstractionModule->GetWebLoadRequestFactory(),
        *m_pNetworkCapabilities,
        m_pWindowsPlatformAbstractionModule->GetUrlEncoder()
        );

    m_pWindowsFlurryMetricsService = Eegeo_NEW(ExampleApp::Metrics::WindowsFlurryMetricsService)(&m_nativeState);

    typedef ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationModule ApplicationConfigurationModule;
    ApplicationConfigurationModule applicationConfigurationModule(m_pWindowsPlatformAbstractionModule->GetFileIO(), "Development Build", "0.0.1");

    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(
        ExampleApp::ApiKey,
        *m_pWindowsPlatformAbstractionModule,
        screenProperties,
        *m_pWindowsLocationService,
        m_WindowsNativeUIFactories,
        platformConfig,
        *m_pJpegLoader,
        *m_pInitialExperienceModule,
        *m_pWindowsPersistentSettingsModel,
        m_messageBus,
        m_sdkDomainEventBus,
        *m_pNetworkCapabilities,
        m_searchServiceModules,
        *m_pWindowsFlurryMetricsService,
        applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration("ApplicationConfigs/standard_config.json"),
        *this);

    m_pModalBackgroundNativeViewModule = Eegeo_NEW(ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeViewModule)(
        m_pApp->World().GetRenderingModule(),
        m_messageBus);

    m_pWindowsPlatformAbstractionModule->SetWebRequestServiceWorkPool(m_pApp->World().GetWorkPool());

    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp);
    m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
}

AppHost::~AppHost()
{
    ASSERT_NATIVE_THREAD

        m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    Eegeo_DELETE m_pApp;
    m_pApp = NULL;

    Eegeo_DELETE m_pWindowsFlurryMetricsService;
    m_pWindowsFlurryMetricsService = NULL;

    for (std::map<std::string, ExampleApp::Search::SdkModel::ISearchServiceModule*>::iterator it = m_searchServiceModules.begin(); it != m_searchServiceModules.end(); ++it)
    {
        Eegeo_DELETE(*it).second;
    }
    m_searchServiceModules.clear();

    Eegeo_DELETE m_pNetworkCapabilities;
    m_pNetworkCapabilities = NULL;

    Eegeo_DELETE m_pInitialExperienceModule;
    m_pInitialExperienceModule = NULL;

	Eegeo_DELETE m_pWindowsPersistentSettingsModel;
	m_pWindowsPersistentSettingsModel = NULL;

    Eegeo_DELETE m_pInputProcessor;
    m_pInputProcessor = NULL;

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();

    Eegeo_DELETE m_pWindowsPlatformAbstractionModule;
    m_pWindowsPlatformAbstractionModule = NULL;

    Eegeo_DELETE m_pJpegLoader;
    m_pJpegLoader = NULL;

    Eegeo_DELETE m_pWindowsConnectivityService;
    m_pWindowsConnectivityService = NULL;

    Eegeo_DELETE m_pWindowsLocationService;
    m_pWindowsLocationService = NULL;
}

void AppHost::OnResume()
{
    ASSERT_NATIVE_THREAD

        m_pApp->OnResume();
    m_isPaused = false;
}

void AppHost::OnPause()
{
    ASSERT_NATIVE_THREAD

        m_isPaused = true;
    m_pApp->OnPause();
    m_pWindowsLocationService->StopListening();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
    ASSERT_NATIVE_THREAD

        m_pWindowsPlatformAbstractionModule->UpdateSurface(sharedSurface);
}

void AppHost::SetViewportOffset(float x, float y)
{
    ASSERT_NATIVE_THREAD

        m_inputHandler.SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Windows::Input::TouchInputEvent& event)
{
    ASSERT_NATIVE_THREAD

        m_pInputProcessor->HandleInput(event, m_nativeState.screenWidth, m_nativeState.screenHeight);
}

void AppHost::HandleKeyboardInputEvent(const Eegeo::Windows::Input::KeyboardInputEvent& event)
{
    m_pInputProcessor->HandleInput(event);

    ExampleApp::FlattenButton::View::FlattenButtonViewModule* flattenButton = dynamic_cast<ExampleApp::FlattenButton::View::FlattenButtonViewModule*>(m_pFlattenButtonViewModule);
    ExampleApp::Compass::View::CompassViewModule* compass = dynamic_cast<ExampleApp::Compass::View::CompassViewModule*>(m_pCompassViewModule);
    ExampleApp::MyPinCreation::View::MyPinCreationViewModule* pin = dynamic_cast<ExampleApp::MyPinCreation::View::MyPinCreationViewModule*>(m_pMyPinCreationViewModule);

    if (event.keyCode == VK_UP)
    {
        flattenButton->AnimateOnScreen();
        compass->AnimateOnScreen();
        pin->AnimateOnScreen();
    }
    else if (event.keyCode == VK_DOWN)
    {
        flattenButton->AnimateOffScreen();
        compass->AnimateOffScreen();
        pin->AnimateOffScreen();
    }
}

void AppHost::SetAllInputEventsToPointerUp(int x, int y)
{
    m_pInputProcessor->SetAllInputEventsToPointerUp(x, y);
}

void AppHost::Update(float dt)
{
    ASSERT_NATIVE_THREAD

        if (m_isPaused)
        {
            return;
        }

    m_messageBus.FlushToNative();

    m_pApp->Update(dt);

    m_pModalBackgroundNativeViewModule->Update(dt);

    if (m_pApp->IsLoadingScreenComplete() && !m_requestedApplicationInitialiseViewState)
    {
        m_requestedApplicationInitialiseViewState = true;
        DispatchRevealUiMessageToUiThreadFromNativeThread();
    }
}

void AppHost::Draw(float dt)
{
    ASSERT_NATIVE_THREAD

        if (m_isPaused)
        {
            return;
        }

    m_pApp->Draw(dt);
    m_pInputProcessor->Update(dt);
}

void AppHost::HandleApplicationUiCreatedOnNativeThread()
{
    ASSERT_NATIVE_THREAD

        m_uiCreatedMessageReceivedOnNativeThread = true;
}

void AppHost::DispatchRevealUiMessageToUiThreadFromNativeThread()
{
    ASSERT_NATIVE_THREAD

    RevealUiFromUiThread();
}

void AppHost::DispatchUiCreatedMessageToNativeThreadFromUiThread()
{
    ASSERT_UI_THREAD

    HandleApplicationUiCreatedOnNativeThread();
}

void AppHost::RevealUiFromUiThread()
{
    ASSERT_UI_THREAD

    m_pApp->InitialiseApplicationViewState();
}

void AppHost::CreateUiFromUiThread()
{
    ASSERT_UI_THREAD

        Eegeo_ASSERT(!m_createdUIModules);
    CreateApplicationViewModulesFromUiThread();
    DispatchUiCreatedMessageToNativeThreadFromUiThread();
}

void AppHost::UpdateUiViewsFromUiThread(float dt)
{
    ASSERT_UI_THREAD

        m_messageBus.FlushToUi();

    if (m_createdUIModules)
    {
        m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel().UpdateObjectsUiThread(dt);
    }
    else
    {
        CreateUiFromUiThread();
    }
}

void AppHost::DestroyUiFromUiThread()
{
    ASSERT_UI_THREAD

        DestroyApplicationViewModulesFromUiThread();
}

void AppHost::CreateApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD

        m_createdUIModules = true;
    ExampleApp::MobileExampleApp& app = *m_pApp;

    m_pWatermarkViewModule = Eegeo_NEW(ExampleApp::Watermark::View::WatermarkViewModule)(
        m_nativeState,
        app.WatermarkModule().GetWatermarkViewModel(),
		app.WatermarkModule().GetWatermarkDataRepository(),
        m_messageBus,
        *m_pWindowsFlurryMetricsService
        );

    // 3d map view layer.
    m_pWorldPinOnMapViewModule = Eegeo_NEW(ExampleApp::WorldPins::View::WorldPinOnMapViewModule)(
        m_nativeState,
        app.WorldPinsModule().GetWorldPinInFocusViewModel(),
        app.WorldPinsModule().GetScreenControlViewModel(),
        app.ModalityModule().GetModalityModel(),
        app.GetAppModeModel(),
        app.PinDiameter()
        );

    // HUD behind modal background layer.
    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::View::FlattenButtonViewModule)(
        m_nativeState,
        app.FlattenButtonModule().GetFlattenButtonViewModel(),
        m_messageBus,
        *m_pWindowsFlurryMetricsService
        );

    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::View::CompassViewModule)(
        m_nativeState,
        app.CompassModule().GetCompassViewModel(),
        m_messageBus
        );

	m_pMyPinCreationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationViewModule)(
		m_nativeState,
		app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
		app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
		app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
		m_messageBus,
		*m_pWindowsFlurryMetricsService
		);

    // Modal background layer.
    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewModule)(
        m_nativeState,
        app.ModalityModule().GetModalityModel(),
        m_messageBus
        );

    m_pSecondaryMenuViewModule = Eegeo_NEW(ExampleApp::SecondaryMenu::View::SecondaryMenuViewModule)(
        "ExampleAppWPF.SecondaryMenuView",
        m_nativeState,
        app.SecondaryMenuModule().GetSecondaryMenuModel(),
        app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
        m_messageBus
        );

    m_pSearchResultMenuViewModule = Eegeo_NEW(ExampleApp::SearchResultMenu::View::SearchMenuViewModule)(
        "ExampleAppWPF.SearchMenuView",
        m_nativeState,
        app.SearchResultMenuModule().GetSearchResultMenuModel(),
        app.SearchResultMenuModule().GetMenuViewModel(),
        app.CategorySearchModule().GetCategorySearchRepository(),
        app.SearchResultMenuModule().GetSearchResultMenuViewModel(),
        app.SearchResultMenuModule().GetSearchResultMenuOptionsModel(),
        app.SearchResultMenuModule().GetSearchResultMenuOrder(),
        app.GetAppModeModel(),
        m_messageBus
        );

    // Pop-up layer.
    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule)(
        m_nativeState,
        app.SearchResultPoiModule().GetSearchResultPoiViewModel(),
        m_messageBus,
        *m_pWindowsFlurryMetricsService
        );

    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewModule)(
        m_nativeState,
        app.AboutPageModule().GetAboutPageViewModel(),
        *m_pWindowsFlurryMetricsService
        );


    m_pOptionsViewModule = Eegeo_NEW(ExampleApp::Options::View::OptionsViewModule)(
        m_nativeState,
        app.OptionsModule().GetOptionsViewModel(),
        m_pWindowsPlatformAbstractionModule->GetWindowsHttpCache(),
        m_messageBus);

    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
        m_nativeState,
        app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
        *m_pWindowsConnectivityService,
        m_messageBus,
        *m_pWindowsFlurryMetricsService
        );

    m_pMyPinDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinDetails::View::MyPinDetailsViewModule)(
        m_nativeState,
        app.MyPinDetailsModule().GetMyPinDetailsViewModel(),
        m_messageBus
        );

    // Initial UX layer
    m_pInitialExperienceIntroViewModule = Eegeo_NEW(ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule)(
        m_nativeState,
        m_messageBus
        );

	m_pInteriorsExplorerViewModule = Eegeo_NEW(ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule)(
		app.InteriorsExplorerModule().GetInteriorsExplorerViewModel(),
		m_messageBus,
		app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
		app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
		app.SearchResultMenuModule().GetMenuViewModel(),
		app.FlattenButtonModule().GetScreenControlViewModel(),
		app.CompassModule().GetScreenControlViewModel(),
		app.WatermarkModule().GetScreenControlViewModel(),
		app.GetIdentityProvider());

    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule);

    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();

    viewControllerUpdaterModel.AddUpdateableObject(m_pSecondaryMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSearchResultMenuViewModule->GetMenuController());
}

void AppHost::DestroyApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD

        if (m_createdUIModules)
        {
            Eegeo_DELETE m_pMyPinDetailsViewModule;

            Eegeo_DELETE m_pViewControllerUpdaterModule;

            Eegeo_DELETE m_pMyPinCreationDetailsViewModule;

            Eegeo_DELETE m_pFlattenButtonViewModule;

            Eegeo_DELETE m_pMyPinCreationViewModule;

            Eegeo_DELETE m_pOptionsViewModule;

            Eegeo_DELETE m_pAboutPageViewModule;

            Eegeo_DELETE m_pWorldPinOnMapViewModule;

            Eegeo_DELETE m_pSearchResultPoiViewModule;

            Eegeo_DELETE m_pModalBackgroundViewModule;

            Eegeo_DELETE m_pSearchResultMenuViewModule;

            Eegeo_DELETE m_pSecondaryMenuViewModule;

            Eegeo_DELETE m_pCompassViewModule;

            Eegeo_DELETE m_pInitialExperienceIntroViewModule;

			Eegeo_DELETE m_pInteriorsExplorerViewModule;

            Eegeo_DELETE m_pWatermarkViewModule;
        }
    m_createdUIModules = false;
}

void AppHost::HandleFailureToProvideWorkingApiKey()
{
    m_WindowsAlertBoxFactory.CreateSingleOptionAlertBox
        (
            "Bad API Key",
            "You must provide a valid API key to the constructor of EegeoWorld. See the readme file for details.",
            m_failAlertHandler
            );
}

void AppHost::HandleFailureToDownloadBootstrapResources()
{
    std::string message =
        m_pNetworkCapabilities->StreamOverWifiOnly()
        ? "Unable to download required data! Please ensure you have a Wi-fi connection the next time you attempt to run this application."
        : "Unable to download required data! Please ensure you have an Internet connection the next time you attempt to run this application.";

    m_WindowsAlertBoxFactory.CreateSingleOptionAlertBox("Error", message, m_failAlertHandler);
}

void AppHost::HandleStartupFailure()
{
    exit(1);
}
