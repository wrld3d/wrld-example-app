// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppHost.h"
#include "AndroidWebRequestService.hpp"
#include "AndroidSharedGlContext.h"
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
#include "AndroidThreadHelper.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "LoadingScreen.h"
#include "PlatformConfig.h"
#include "AndroidPlatformConfigBuilder.h"
#include "AndroidUrlEncoder.h"
#include "AndroidFileIO.h"
#include "AndroidLocationService.h"
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
#include "AndroidPlatformAbstractionModule.h"
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
#include "AndroidInitialExperienceModule.h"
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
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchResultRepositoryObserver.h"
#include "IMyPinsModule.h"
#include "ApiKey.h"
#include "OptionsViewModule.h"
#include "OptionsView.h"
#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "NetworkCapabilities.h"
#include "AndroidYelpSearchServiceModule.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "SearchVendorNames.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    AndroidNativeState& nativeState,
    Eegeo::Rendering::ScreenProperties screenProperties,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
    :m_isPaused(false)
    ,m_pJpegLoader(NULL)
    ,m_pAndroidLocationService(NULL)
    ,m_pAndroidConnectivityService(NULL)
    ,m_nativeState(nativeState)
    ,m_androidInputBoxFactory(&nativeState)
    ,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
    ,m_androidAlertBoxFactory(&nativeState)
    ,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
    ,m_pInputProcessor(NULL)
    ,m_pAndroidPlatformAbstractionModule(NULL)
    ,m_pSecondaryMenuViewModule(NULL)
    ,m_pSearchResultMenuViewModule(NULL)
    ,m_pModalBackgroundViewModule(NULL)
    ,m_pFlattenButtonViewModule(NULL)
    ,m_pMyPinCreationViewModule(NULL)
    ,m_pMyPinCreationDetailsViewModule(NULL)
    ,m_pMyPinDetailsViewModule(NULL)
    ,m_pSearchResultPoiViewModule(NULL)
    ,m_pWorldPinOnMapViewModule(NULL)
    ,m_pCompassViewModule(NULL)
    ,m_pApp(NULL)
    ,m_androidPersistentSettingsModel(nativeState)
    ,m_createdUIModules(false)
    ,m_requestedApplicationInitialiseViewState(false)
    ,m_uiCreatedMessageReceivedOnNativeThread(false)
    ,m_pViewControllerUpdaterModule(NULL)
	,m_pAndroidFlurryMetricsService(NULL)
	,m_pInitialExperienceIntroViewModule(NULL)
	,m_searchServiceModules()
	,m_failAlertHandler(this, &AppHost::HandleStartupFailure)
	,m_cameraTransitionChangedHandler(this, &AppHost::HandleCameraTransitionChanged)
{
    ASSERT_NATIVE_THREAD

    Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

    Eegeo::TtyHandler::TtyEnabled = true;
    Eegeo::AssertHandler::BreakOnAssert = true;

    m_pAndroidLocationService = Eegeo_NEW(AndroidLocationService)(&nativeState);
    m_pAndroidConnectivityService = Eegeo_NEW(AndroidConnectivityService)(&nativeState);

    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

    std::set<std::string> customApplicationAssetDirectories;
    customApplicationAssetDirectories.insert("SearchResultOnMap");
    customApplicationAssetDirectories.insert("ApplicationConfigs");

    m_pAndroidPlatformAbstractionModule = Eegeo_NEW(Eegeo::Android::AndroidPlatformAbstractionModule)(
            nativeState,
            *m_pJpegLoader,
            display,
            resourceBuildShareContext,
            shareSurface,
            ExampleApp::ApiKey,
            customApplicationAssetDirectories);

    Eegeo::EffectHandler::Initialise();

    std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
    Eegeo::Config::PlatformConfig platformConfig = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();
    platformConfig.OptionsConfig.InteriorsControlledByApp = true;

    m_pInputProcessor = Eegeo_NEW(Eegeo::Android::Input::AndroidInputProcessor)(&m_inputHandler, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

    m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::SdkModel::AndroidInitialExperienceModule)(
                                     m_nativeState,
                                     m_androidPersistentSettingsModel,
                                     m_messageBus
                                 );

    m_pNetworkCapabilities = Eegeo_NEW(ExampleApp::Net::SdkModel::NetworkCapabilities)(
    		*m_pAndroidConnectivityService,
    		m_pAndroidPlatformAbstractionModule->GetHttpCache(),
    		m_androidPersistentSettingsModel);

    m_searchServiceModules[ExampleApp::Search::YelpVendorName] = Eegeo_NEW(ExampleApp::Search::Yelp::AndroidYelpSearchServiceModule)(
    		nativeState,
    		m_pAndroidPlatformAbstractionModule->GetWebLoadRequestFactory(),
    		*m_pNetworkCapabilities,
    		m_pAndroidPlatformAbstractionModule->GetUrlEncoder()
    );

    m_pAndroidFlurryMetricsService = Eegeo_NEW(ExampleApp::Metrics::AndroidFlurryMetricsService)(&m_nativeState);

    typedef ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationModule ApplicationConfigurationModule;
    ApplicationConfigurationModule applicationConfigurationModule(m_pAndroidPlatformAbstractionModule->GetFileIO());

    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(
                 ExampleApp::ApiKey,
                 *m_pAndroidPlatformAbstractionModule,
                 screenProperties,
                 *m_pAndroidLocationService,
                 m_androidNativeUIFactories,
                 platformConfig,
                 *m_pJpegLoader,
                 *m_pInitialExperienceModule,
                 m_androidPersistentSettingsModel,
                 m_messageBus,
                 m_sdkDomainEventBus,
                 *m_pNetworkCapabilities,
                 m_searchServiceModules,
                 *m_pAndroidFlurryMetricsService,
                 applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration("ApplicationConfigs/standard_config.json"),
                 *this);

    m_pModalBackgroundNativeViewModule = Eegeo_NEW(ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeViewModule)(
            m_pApp->World().GetRenderingModule(),
            m_messageBus);

    m_pAndroidPlatformAbstractionModule->SetWebRequestServiceWorkPool(m_pApp->World().GetWorkPool());

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

    Eegeo_DELETE m_pAndroidFlurryMetricsService;
    m_pAndroidFlurryMetricsService = NULL;

	for(std::map<std::string, ExampleApp::Search::SdkModel::ISearchServiceModule*>::iterator it = m_searchServiceModules.begin(); it != m_searchServiceModules.end(); ++it)
	{
		Eegeo_DELETE (*it).second;
	}
	m_searchServiceModules.clear();

    Eegeo_DELETE m_pNetworkCapabilities;
    m_pNetworkCapabilities = NULL;

    Eegeo_DELETE m_pInitialExperienceModule;
    m_pInitialExperienceModule = NULL;

    Eegeo_DELETE m_pInputProcessor;
    m_pInputProcessor = NULL;

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();

    Eegeo_DELETE m_pAndroidPlatformAbstractionModule;
    m_pAndroidPlatformAbstractionModule = NULL;

    Eegeo_DELETE m_pJpegLoader;
    m_pJpegLoader = NULL;

    Eegeo_DELETE m_pAndroidConnectivityService;
    m_pAndroidConnectivityService = NULL;

    Eegeo_DELETE m_pAndroidLocationService;
    m_pAndroidLocationService = NULL;
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
    m_pAndroidLocationService->StopListening();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
    ASSERT_NATIVE_THREAD

    m_pAndroidPlatformAbstractionModule->UpdateSurface(sharedSurface);
}

void AppHost::SetViewportOffset(float x, float y)
{
    ASSERT_NATIVE_THREAD

    m_inputHandler.SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
    ASSERT_NATIVE_THREAD

    m_pInputProcessor->HandleInput(event);
}

void AppHost::Update(float dt)
{
    ASSERT_NATIVE_THREAD

    if(m_isPaused)
    {
        return;
    }

    m_messageBus.FlushToNative();

    m_pApp->Update(dt);

    m_pModalBackgroundNativeViewModule->Update(dt);

    if(m_pApp->IsLoadingScreenComplete() && !m_requestedApplicationInitialiseViewState)
    {
        m_requestedApplicationInitialiseViewState = true;
        DispatchRevealUiMessageToUiThreadFromNativeThread();
    }
}

void AppHost::Draw(float dt)
{
    ASSERT_NATIVE_THREAD

    if(m_isPaused)
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

    AndroidSafeNativeThreadAttachment attached(m_nativeState);
    JNIEnv* env = attached.envForThread;
    jmethodID dispatchRevealUiMessageToUiThreadFromNativeThread = env->GetMethodID(m_nativeState.activityClass, "dispatchRevealUiMessageToUiThreadFromNativeThread", "(J)V");
    env->CallVoidMethod(m_nativeState.activity, dispatchRevealUiMessageToUiThreadFromNativeThread, (jlong)(this));
}

void AppHost::DispatchUiCreatedMessageToNativeThreadFromUiThread()
{
    ASSERT_UI_THREAD

    AndroidSafeNativeThreadAttachment attached(m_nativeState);
    JNIEnv* env = attached.envForThread;
    jmethodID dispatchUiCreatedMessageToNativeThreadFromUiThread = env->GetMethodID(m_nativeState.activityClass, "dispatchUiCreatedMessageToNativeThreadFromUiThread", "(J)V");
    env->CallVoidMethod(m_nativeState.activity, dispatchUiCreatedMessageToNativeThreadFromUiThread, (jlong)(this));
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

    if(m_createdUIModules)
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
		m_messageBus,
		*m_pAndroidFlurryMetricsService,
        app.GetApplicationConfiguration().GoogleAnalyticsReferrerToken()
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
                                     *m_pAndroidFlurryMetricsService,
                                     app.GetAppModeModel()
                                 );

    m_pMyPinCreationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationViewModule)(
                                     m_nativeState,
                                     app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                     app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
                                     app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                     m_messageBus,
                                     *m_pAndroidFlurryMetricsService,
                                     app.GetAppModeModel()
                                 );


    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::View::CompassViewModule)(
                               m_nativeState,
                               app.CompassModule().GetCompassViewModel(),
                               m_messageBus
                           );

    // Modal background layer.
    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewModule)(
                                       m_nativeState,
                                       app.ModalityModule().GetModalityModel(),
                                       m_messageBus
                                   );

    m_pSecondaryMenuViewModule = Eegeo_NEW(ExampleApp::SecondaryMenu::View::SecondaryMenuViewModule)(
                                     "com/eegeo/secondarymenu/SecondaryMenuView",
                                     m_nativeState,
                                     app.SecondaryMenuModule().GetSecondaryMenuModel(),
                                     app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
                                     m_messageBus
                                 );

    m_pSearchResultMenuViewModule = Eegeo_NEW(ExampleApp::SearchResultMenu::View::SearchMenuViewModule)(
                                        "com/eegeo/searchmenu/SearchMenuView",
                                        m_nativeState,
                                        app.SearchResultMenuModule().GetSearchResultMenuModel(),
                                        app.SearchResultMenuModule().GetMenuViewModel(),
                                        app.CategorySearchModule().GetCategorySearchRepository(),
                                        app.SearchResultMenuModule().GetSearchResultMenuViewModel(),
	                                    app.SearchResultMenuModule().GetSearchResultMenuOptionsModel(),
	                                    app.SearchResultMenuModule().GetSearchResultMenuOrder(),
                                        m_messageBus
                                    );

    // Pop-up layer.
    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule)(
                                       m_nativeState,
                                       app.SearchResultPoiModule().GetSearchResultPoiViewModel(),
                                       m_messageBus,
                                       *m_pAndroidFlurryMetricsService
                                   );

    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewModule)(
                                 m_nativeState,
                                 app.AboutPageModule().GetAboutPageViewModel(),
                                 *m_pAndroidFlurryMetricsService
                             );


    m_pOptionsViewModule = Eegeo_NEW(ExampleApp::Options::View::OptionsViewModule)(
    		m_nativeState,
    		app.OptionsModule().GetOptionsViewModel(),
    		m_pAndroidPlatformAbstractionModule->GetAndroidHttpCache(),
    		m_messageBus);

    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
                                            m_nativeState,
                                            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                            *m_pAndroidConnectivityService,
                                            m_messageBus,
                                            *m_pAndroidFlurryMetricsService
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

    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule);

    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();

    viewControllerUpdaterModel.AddUpdateableObject(m_pSecondaryMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSearchResultMenuViewModule->GetMenuController());

    m_messageBus.SubscribeUi(m_cameraTransitionChangedHandler);
}

void AppHost::DestroyApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD

    if(m_createdUIModules)
    {
    	m_messageBus.UnsubscribeUi(m_cameraTransitionChangedHandler);

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

        Eegeo_DELETE m_pWatermarkViewModule;
    }
    m_createdUIModules = false;
}

void AppHost::HandleFailureToProvideWorkingApiKey()
{
	m_androidAlertBoxFactory.CreateSingleOptionAlertBox
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

	m_androidAlertBoxFactory.CreateSingleOptionAlertBox("Error", message, m_failAlertHandler);
}

void AppHost::HandleStartupFailure()
{
	exit(1);
}


void AppHost::HandleCameraTransitionChanged(const ExampleApp::CameraTransitions::CameraTransitionChangedMessage& message)
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	                JNIEnv* env = attached.envForThread;

	const std::string methodName = "setTouchEnabled";
	jmethodID touchEnabledMethod = env->GetMethodID(m_nativeState.activityClass, methodName.c_str(), "(Z)V");
	env->CallVoidMethod(m_nativeState.activity, touchEnabledMethod, !message.IsTransitionInProgress());
}

