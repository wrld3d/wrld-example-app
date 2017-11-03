// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <set>

#include "AboutPageViewModule.h"
#include "AndroidApplicationConfigurationVersionProvider.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidImageNameHelper.h"
#include "AndroidInitialExperienceModule.h"
#include "AndroidMenuReactionModel.h"
#include "AndroidPlatformAbstractionModule.h"
#include "AndroidPlatformConfigBuilder.h"
#include "AndroidAutomatedScreenshotController.h"
#include "ApiKey.h"
#include "AppHost.h"
#include "AppInterface.h"
#include "ApplicationConfiguration.h"
#include "ApplicationConfigurationModule.h"
#include "AssertHandler.h"
#include "CompassViewModule.h"
#include "ConnectivityChangedViewMessage.h"
#include "CurrentLocationService.h"
#include "EegeoWorld.h"
#include "EffectHandler.h"
#include "EGL/egl.h"
#include "FlattenButtonViewModule.h"
#include "IAboutPageModule.h"
#include "ICompassModule.h"
#include "IFlattenButtonModule.h"
#include "IInteriorsExplorerModule.h"
#include "IModalityModule.h"
#include "IMyPinCreationDetailsModule.h"
#include "IMyPinCreationModule.h"
#include "IMyPinDetailsModule.h"
#include "InitialExperienceIntroViewModule.h"
#include "InteriorsExplorerViewModule.h"
#include "InteriorMetaDataModule.h"
#include "IOptionsModule.h"
#include "ISearchMenuModule.h"
#include "ISearchResultPoiModule.h"
#include "ISearchResultSectionModule.h"
#include "ISettingsMenuModule.h"
#include "ITagSearchModule.h"
#include "IViewControllerUpdaterModel.h"
#include "IWatermarkModule.h"
#include "jni.h"
#include "JpegLoader.h"
#include "MenuController.h"
#include "MobileExampleApp.h"
#include "ModalBackgroundNativeViewModule.h"
#include "ModalBackgroundViewModule.h"
#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationViewModule.h"
#include "MyPinDetailsViewModule.h"
#include "NetworkCapabilities.h"
#include "OptionsViewModule.h"
#include "PlatformConfig.h"
#include "ScreenProperties.h"
#include "SearchMenuViewModule.h"
#include "SearchResultPoiViewModule.h"
#include "SearchResultSectionViewModule.h"
#include "SettingsMenuViewModule.h"
#include "TagSearchViewModule.h"
#include "TtyHandler.h"
#include "UserInteractionEnabledChangedMessage.h"
#include "ViewControllerUpdaterModule.h"
#include "WatermarkViewModule.h"
#include "WebConnectivityValidator.h"
#include "SurveyViewModule.h"
#include "SenionLabBroadcastReceiver.h"
#include "AndroidAutomatedScreenshotController.h"
#include "AutomatedScreenshotController.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

namespace
{
	ExampleApp::ApplicationConfig::ApplicationConfiguration LoadApplicationConfiguration(AndroidNativeState& nativeState, const std::set<std::string>& customApplicationAssetDirectories)
	{
	    AndroidFileIO tempFileIO(&nativeState, customApplicationAssetDirectories);
	    ExampleApp::ApplicationConfig::SdkModel::AndroidApplicationConfigurationVersionProvider versionProvider(nativeState);

	    return ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(
	    		tempFileIO,
	    		versionProvider,
	    		ExampleApp::ApplicationConfigurationPath);
	}
}

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
    ,m_pCurrentLocationService(NULL)
    ,m_pAndroidConnectivityService(NULL)
    ,m_nativeState(nativeState)
    ,m_androidInputBoxFactory(&nativeState)
    ,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
    ,m_androidAlertBoxFactory(&nativeState)
    ,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
    ,m_pInputProcessor(NULL)
    ,m_pAndroidPlatformAbstractionModule(NULL)
    ,m_pSearchMenuViewModule(NULL)
	,m_pSettingsMenuViewModule(NULL)
	,m_pSearchResultSectionViewModule(NULL)
    ,m_pModalBackgroundViewModule(NULL)
    ,m_pFlattenButtonViewModule(NULL)
    ,m_pMyPinCreationViewModule(NULL)
    ,m_pMyPinCreationDetailsViewModule(NULL)
    ,m_pMyPinDetailsViewModule(NULL)
    ,m_pSearchResultPoiViewModule(NULL)
    ,m_pCompassViewModule(NULL)
    ,m_pApp(NULL)
    ,m_androidPersistentSettingsModel(nativeState)
    ,m_createdUIModules(false)
    ,m_requestedApplicationInitialiseViewState(false)
    ,m_uiCreatedMessageReceivedOnNativeThread(false)
    ,m_pViewControllerUpdaterModule(NULL)
	,m_pAndroidFlurryMetricsService(NULL)
	,m_pInitialExperienceIntroViewModule(NULL)
    ,m_pTagSearchViewModule(NULL)
	,m_failAlertHandler(this, &AppHost::HandleStartupFailure)
	,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
    ,m_pSenionLabLocationModule(NULL)
    ,m_pIndoorAtlasLocationModule(NULL)
    ,m_pInteriorsLocationServiceModule(NULL)
    ,m_pSenionLabBroadcastReceiver(NULL)
    ,m_pAndroidAutomatedScreenshotController(NULL)
    ,m_surfaceScreenshotService(screenProperties)
    ,m_screenshotService(m_nativeState, m_surfaceScreenshotService)
{
    ASSERT_NATIVE_THREAD

    Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

    Eegeo::TtyHandler::TtyEnabled = true;
    Eegeo::AssertHandler::BreakOnAssert = true;

    m_pAndroidLocationService = Eegeo_NEW(AndroidLocationService)(&nativeState);
    m_pCurrentLocationService = Eegeo_NEW(Eegeo::Helpers::CurrentLocationService::CurrentLocationService)(*m_pAndroidLocationService);
    m_pAndroidConnectivityService = Eegeo_NEW(AndroidConnectivityService)(&nativeState);

    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

    std::set<std::string> customApplicationAssetDirectories;
    customApplicationAssetDirectories.insert("SearchResultOnMap");
    customApplicationAssetDirectories.insert("ApplicationConfigs");

    const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration = LoadApplicationConfiguration(nativeState, customApplicationAssetDirectories);
	
    m_pAndroidPlatformAbstractionModule = Eegeo_NEW(Eegeo::Android::AndroidPlatformAbstractionModule)(
            nativeState,
            *m_pJpegLoader,
            display,
            resourceBuildShareContext,
            shareSurface,
            applicationConfiguration.EegeoApiKey(),
            customApplicationAssetDirectories);

    Eegeo::EffectHandler::Initialise();

    std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
    Eegeo::Android::AndroidImageNameHelper imageHelper(&nativeState);
    Eegeo::Android::AndroidPlatformConfigBuilder androidPlatformConfigBuilder(deviceModel,
																			  imageHelper.GetImageResolutionSuffix(),
																			  imageHelper.GetImageResolutionScale());

    const Eegeo::Config::PlatformConfig& platformConfiguration = ExampleApp::ApplicationConfig::SdkModel::BuildPlatformConfig(androidPlatformConfigBuilder, applicationConfiguration);

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

    m_pAndroidFlurryMetricsService = Eegeo_NEW(ExampleApp::Metrics::AndroidFlurryMetricsService)(&m_nativeState);

    m_pMenuReactionModel = Eegeo_NEW(ExampleApp::Menu::View::AndroidMenuReactionModel)();

    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(
    			 applicationConfiguration,
                 *m_pAndroidPlatformAbstractionModule,
                 screenProperties,
                 *m_pCurrentLocationService,
                 m_androidNativeUIFactories,
                 platformConfiguration,
                 *m_pJpegLoader,
                 *m_pInitialExperienceModule,
                 m_androidPersistentSettingsModel,
                 m_messageBus,
                 m_sdkDomainEventBus,
                 *m_pNetworkCapabilities,
                 *m_pAndroidFlurryMetricsService,
                 *this,
                 *m_pMenuReactionModel,
                 m_userIdleService,
                 m_screenshotService);

    Eegeo::Modules::Map::MapModule& mapModule = m_pApp->World().GetMapModule();
    Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
    m_pSenionLabLocationModule = Eegeo_NEW(ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationModule)(m_pApp->GetAppModeModel(),
                                                                                                                        interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                                        interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                        mapModule.GetEnvironmentFlatteningService(),
                                                                                                                        *m_pAndroidLocationService,
                                                                                                                        mapModule.GetInteriorMetaDataModule().GetInteriorMetaDataRepository(),
                                                                                                                        m_messageBus,
                                                                                                                        m_nativeState);

    m_pIndoorAtlasLocationModule = Eegeo_NEW(ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationModule)(m_pApp->GetAppModeModel(),
                                                                                                                              interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                                              interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                              mapModule.GetEnvironmentFlatteningService(),
                                                                                                                              *m_pAndroidLocationService,
                                                                                                                              mapModule.GetInteriorMetaDataModule().GetInteriorMetaDataRepository(),
																															  m_messageBus,
                                                                                                                              m_nativeState);

    const std::map<std::string, Eegeo::Location::ILocationService&> interiorLocationServices{{"Senion", m_pSenionLabLocationModule->GetLocationService()},
                                                                                             {"IndoorAtlas", m_pIndoorAtlasLocationModule->GetLocationService()}};
    m_pInteriorsLocationServiceModule = Eegeo_NEW(ExampleApp::InteriorsPosition::SdkModel::InteriorsLocationServiceModule)(m_pApp->InteriorsExplorerModule().GetInteriorsExplorerModel(),
                                                                                                                           interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                           *m_pCurrentLocationService,
                                                                                                                           *m_pAndroidLocationService,
                                                                                                                           interiorLocationServices,
                                                                                                                           mapModule.GetInteriorMetaDataModule().GetInteriorMetaDataRepository(),
																														   interiorsPresentationModule.GetInteriorInteractionModel(),
																														   m_pApp->CameraTransitionController(),
																														   m_pApp->CompassModule().GetCompassModel(),
                                                                                                                           m_messageBus);

    m_pModalBackgroundNativeViewModule = Eegeo_NEW(ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeViewModule)(
            m_pApp->World().GetRenderingModule(),
            m_messageBus);

    ExampleApp::Automation::AutomatedScreenshotController* screenshotController = m_pApp->AutomatedScreenshotController();
    if (NULL != screenshotController)
    {
        m_pAndroidAutomatedScreenshotController = Eegeo_NEW(ExampleApp::Automation::SdkModel::AndroidAutomatedScreenshotController)(nativeState, *screenshotController);
    }

    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp);
    m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
}

AppHost::~AppHost()
{
    ASSERT_NATIVE_THREAD

    m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    if (NULL != m_pAndroidAutomatedScreenshotController)
    {
        Eegeo_DELETE m_pAndroidAutomatedScreenshotController;
        m_pAndroidAutomatedScreenshotController = NULL;
    }

    Eegeo_DELETE m_pModalBackgroundNativeViewModule;
    m_pModalBackgroundNativeViewModule = NULL;

    m_pCurrentLocationService->SetLocationService(*m_pAndroidLocationService);

	Eegeo_DELETE m_pInteriorsLocationServiceModule;
	m_pInteriorsLocationServiceModule = NULL;

    Eegeo_DELETE m_pIndoorAtlasLocationModule;
    m_pIndoorAtlasLocationModule = NULL;

	Eegeo_DELETE m_pSenionLabLocationModule;
	m_pSenionLabLocationModule = NULL;

    Eegeo_DELETE m_pApp;
    m_pApp = NULL;

    Eegeo_DELETE m_pMenuReactionModel;
    m_pMenuReactionModel = NULL;

    Eegeo_DELETE m_pAndroidFlurryMetricsService;
    m_pAndroidFlurryMetricsService = NULL;

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

    Eegeo_DELETE m_pCurrentLocationService;
    m_pCurrentLocationService = NULL;

    Eegeo_DELETE m_pAndroidLocationService;
    m_pAndroidLocationService = NULL;
}

void AppHost::OnResume()
{
    ASSERT_NATIVE_THREAD

	m_pSenionLabLocationModule->GetLocationManager().OnResume();
    if(m_pSenionLabBroadcastReceiver != NULL)
    {
        m_pSenionLabBroadcastReceiver->RegisterReceiver();
    }

    m_pApp->OnResume();
    m_isPaused = false;
}

void AppHost::OnPause()
{
    ASSERT_NATIVE_THREAD

    m_isPaused = true;
    m_pApp->OnPause();
    m_pCurrentLocationService->StopListening();

    if (m_pSenionLabBroadcastReceiver != NULL)
    {
        m_pSenionLabBroadcastReceiver->UnregisterReceiver();
    }
    m_pSenionLabLocationModule->GetLocationManager().OnPause();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
    m_surfaceScreenshotService.UpdateScreenProperties(screenProperties);
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

    m_pInteriorsLocationServiceModule->GetController().Update();

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
    m_surfaceScreenshotService.ExecuteScreenshot();
}

void AppHost::HandleApplicationUiCreatedOnNativeThread()
{
    ASSERT_NATIVE_THREAD

    m_uiCreatedMessageReceivedOnNativeThread = true;
    PublishNetworkConnectivityStateToUIThread();
}

void AppHost::PublishNetworkConnectivityStateToUIThread()
{
    // Network validation runs before UI is constructed and so it is not notified and assumed there is no connection: MPLY-6584
    // The state should be passed on opening the UI view, but currently this is done from the UI thread. Pin Creation UI probably needs a refactor.

    ASSERT_NATIVE_THREAD
    
    const Eegeo::Web::WebConnectivityValidator& webConnectivityValidator = m_pApp->World().GetWebConnectivityValidator();
    const bool connectionIsValid = webConnectivityValidator.IsValid();
    m_messageBus.Publish(ExampleApp::Net::ConnectivityChangedViewMessage(connectionIsValid));
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
		app.WatermarkModule().GetWatermarkDataRepository(),
		m_messageBus,
		*m_pAndroidFlurryMetricsService
    );

    // 3d map view layer.

    // HUD behind modal background layer.
    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::View::FlattenButtonViewModule)(
                                     m_nativeState,
                                     app.FlattenButtonModule().GetFlattenButtonViewModel(),
                                     m_messageBus,
                                     *m_pAndroidFlurryMetricsService
                                 );

    m_pMyPinCreationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationViewModule)(
                                     m_nativeState,
                                     app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                     app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
                                     app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                     m_messageBus,
                                     *m_pAndroidFlurryMetricsService
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

    m_pSearchMenuViewModule = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewModule)(
                                        "com/eegeo/searchmenu/SearchMenuView",
                                        m_nativeState,
                                        app.SearchMenuModule().GetSearchMenuModel(),
                                        app.SearchMenuModule().GetSearchMenuViewModel(),
										app.SearchMenuModule().GetSearchSectionViewModel(),
                                        app.TagSearchModule().GetTagSearchRepository(),
	                                    app.SearchMenuModule().GetSearchMenuOptionsModel(),
										m_pModalBackgroundViewModule->GetModalBackgroundView(),
                                        m_messageBus
                                    );

    m_pTagSearchViewModule = ExampleApp::TagSearch::View::TagSearchViewModule::Create(
            app.TagSearchModule().GetTagSearchMenuOptionsModel(),
            app.SettingsMenuModule().GetSettingsMenuViewModel(),
            m_messageBus,
            *m_pMenuReactionModel);

    m_pSettingsMenuViewModule = Eegeo_NEW(ExampleApp::SettingsMenu::View::SettingsMenuViewModule)(
    											"com/eegeo/settingsmenu/SettingsMenuView",
    		                                     m_nativeState,
    		                                     app.SettingsMenuModule().GetSettingsMenuModel(),
    		                                     app.SettingsMenuModule().GetSettingsMenuViewModel(),
												 m_pModalBackgroundViewModule->GetModalBackgroundView(),
    		                                     m_messageBus
    		                                 );

    m_pSearchResultSectionViewModule = Eegeo_NEW(ExampleApp::SearchResultSection::View::SearchResultSectionViewModule)(
    		app.SearchMenuModule().GetSearchMenuViewModel(),
    				    app.SearchResultSectionModule().GetSearchResultSectionOptionsModel(),
    				    app.SearchResultSectionModule().GetSearchResultSectionOrder(),
    				    m_messageBus,
    					*m_pMenuReactionModel,
    		            app.SearchResultPoiModule().GetSearchResultPoiViewModel());

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
                                 *m_pAndroidFlurryMetricsService,
								 m_messageBus);


    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
                                            m_nativeState,
                                            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
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
									m_messageBus,
									app.CameraTransitionController()
								);

    m_pInteriorsExplorerViewModule = Eegeo_NEW(ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule)(
    		app.InteriorsExplorerModule().GetInteriorsExplorerModel(),
			app.InteriorsExplorerModule().GetInteriorsExplorerViewModel(),
            m_messageBus,
            m_nativeState,
            app.GetNavigationService());

    m_pOptionsViewModule = Eegeo_NEW(ExampleApp::Options::View::OptionsViewModule)(
            m_nativeState,
            app.OptionsModule().GetOptionsViewModel(),
            m_pAndroidPlatformAbstractionModule->GetAndroidHttpCache(),
            m_messageBus,
            m_pInteriorsExplorerViewModule->GetController(),
			m_pInitialExperienceIntroViewModule->GetController());

    m_pSurveyViewModule = Eegeo_NEW(ExampleApp::Surveys::View::SurveyViewModule)(m_nativeState, m_messageBus, m_pApp->GetApplicationConfiguration().TimerSurveyUrl());

    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule);

    m_pSenionLabBroadcastReceiver = Eegeo_NEW(ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver)(
            m_pSenionLabLocationModule->GetLocationManager(),
            m_messageBus,
            m_nativeState);
    m_pSenionLabBroadcastReceiver->RegisterReceiver();

    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();

    viewControllerUpdaterModel.AddUpdateableObject(m_pSettingsMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSearchMenuViewModule->GetMenuController());

    SetTouchExclusivity();

    m_messageBus.SubscribeUi(m_userInteractionEnabledChangedHandler);
}

void AppHost::DestroyApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD

    if(m_createdUIModules)
    {
    	m_messageBus.UnsubscribeUi(m_userInteractionEnabledChangedHandler);

    	Eegeo_DELETE m_pSenionLabBroadcastReceiver;

        Eegeo_DELETE m_pViewControllerUpdaterModule;

        Eegeo_DELETE m_pSurveyViewModule;

        Eegeo_DELETE m_pOptionsViewModule;

        Eegeo_DELETE m_pInteriorsExplorerViewModule;

        Eegeo_DELETE m_pInitialExperienceIntroViewModule;

        Eegeo_DELETE m_pMyPinDetailsViewModule;

        Eegeo_DELETE m_pMyPinCreationDetailsViewModule;

        Eegeo_DELETE m_pAboutPageViewModule;

        Eegeo_DELETE m_pSearchResultPoiViewModule;

        Eegeo_DELETE m_pSearchResultSectionViewModule;

        Eegeo_DELETE m_pSettingsMenuViewModule;

        Eegeo_DELETE m_pTagSearchViewModule;

        Eegeo_DELETE m_pSearchMenuViewModule;

        Eegeo_DELETE m_pModalBackgroundViewModule;

        Eegeo_DELETE m_pCompassViewModule;

        Eegeo_DELETE m_pMyPinCreationViewModule;

        Eegeo_DELETE m_pFlattenButtonViewModule;

        Eegeo_DELETE m_pWatermarkViewModule;
    }
    m_createdUIModules = false;
}

void AppHost::SetTouchExclusivity()
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	const std::string methodName = "setTouchExclusivity";
	jmethodID setTouchExclusivityMethod = env->GetMethodID(m_nativeState.activityClass, methodName.c_str(), "()V");
	env->CallVoidMethod(m_nativeState.activity, setTouchExclusivityMethod);
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

void AppHost::HandleNoConnectivityWarning()
{

}

void AppHost::HandleInvalidConnectivityError()
{
	m_androidAlertBoxFactory.CreateSingleOptionAlertBox(
			 "Network error",
			 "Unable to access web reliably. Please check your connection is valid & authenticated.",
			 m_failAlertHandler
			 );
}


void AppHost::HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message)
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	                JNIEnv* env = attached.envForThread;

	const std::string methodName = "setTouchEnabled";
	jmethodID touchEnabledMethod = env->GetMethodID(m_nativeState.activityClass, methodName.c_str(), "(Z)V");
	env->CallVoidMethod(m_nativeState.activity, touchEnabledMethod, message.IsEnabled());
}

void AppHost::HandleOpenUrlEvent(const AppInterface::UrlData& data)
{
	m_pApp->Event_OpenUrl(data);
}
