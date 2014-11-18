// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
#include "PrimaryMenuModule.h"
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
#include "IMenuViewController.h"
#include "CategorySearchModule.h"
#include "ScreenProperties.h"
#include "MyPinCreationViewModule.h"
#include "IMyPinCreationModule.h"
#include "IMyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModule.h"
#include "Logger.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchResultRepositoryObserver.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    AndroidNativeState& nativeState,
    float displayWidth,
    float displayHeight,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
	:m_isPaused(false)
	,m_pJpegLoader(NULL)
	,m_pScreenProperties(NULL)
	,m_pAndroidLocationService(NULL)
	,m_nativeState(nativeState)
	,m_androidInputBoxFactory(&nativeState)
	,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
	,m_androidAlertBoxFactory(&nativeState)
	,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
	,m_pInputProcessor(NULL)
	,m_pAndroidPlatformAbstractionModule(NULL)
	,m_pPrimaryMenuViewModule(NULL)
	,m_pSecondaryMenuViewModule(NULL)
	,m_pSearchResultMenuViewModule(NULL)
	,m_pModalBackgroundViewModule(NULL)
	,m_pFlattenButtonViewModule(NULL)
	,m_pMyPinCreationViewModule(NULL)
	,m_pMyPinCreationDetailsViewModule(NULL)
	,m_pSearchResultPoiViewModule(NULL)
	,m_pWorldPinOnMapViewModule(NULL)
	,m_pCompassViewModule(NULL)
	,m_pApp(NULL)
	,m_androidPersistentSettingsModel(nativeState)
	,m_createdUIModules(false)
	,m_requestedApplicationInitialiseViewState(false)
	,m_uiCreatedMessageReceivedOnNativeThread(false)
	,m_pViewControllerUpdaterModule(NULL)
{
	ASSERT_NATIVE_THREAD

	Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

	Eegeo::TtyHandler::TtyEnabled = true;
	Eegeo::AssertHandler::BreakOnAssert = true;

	m_pAndroidLocationService = Eegeo_NEW(AndroidLocationService)(&nativeState);

	m_pScreenProperties = Eegeo_NEW(Eegeo::Rendering::ScreenProperties)(displayWidth, displayHeight, 1.0f, nativeState.deviceDpi);

	m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

	std::set<std::string> customApplicationAssetDirectories;
	customApplicationAssetDirectories.insert("SearchResultOnMap");

	m_pAndroidPlatformAbstractionModule = Eegeo_NEW(Eegeo::Android::AndroidPlatformAbstractionModule)(
	        nativeState,
	        *m_pJpegLoader,
	        display,
	        resourceBuildShareContext,
	        shareSurface,
	        customApplicationAssetDirectories);

	Eegeo::EffectHandler::Initialise();

	std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
	Eegeo::Config::PlatformConfig platformConfig = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	m_pInputProcessor = Eegeo_NEW(Eegeo::Android::Input::AndroidInputProcessor)(&m_inputHandler, m_pScreenProperties->GetScreenWidth(), m_pScreenProperties->GetScreenHeight());

	m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::AndroidInitialExperienceModule)(
	                                 m_nativeState,
	                                 m_androidPersistentSettingsModel
	                             );

	m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(*m_pAndroidPlatformAbstractionModule,
	         *m_pScreenProperties,
	         *m_pAndroidLocationService,
	         m_androidNativeUIFactories,
	         platformConfig,
	         *m_pJpegLoader,
	         *m_pInitialExperienceModule,
	         m_androidPersistentSettingsModel,
	         m_uiToNativeMessageBus,
	         m_nativeToUiMessageBus);

	m_pModalBackgroundNativeViewModule = Eegeo_NEW(ExampleApp::ModalBackground::ModalBackgroundNativeViewModule)(
	        m_pApp->World().GetRenderingModule(),
	        m_uiToNativeMessageBus
	                                     );

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

	Eegeo::EffectHandler::Reset();
	Eegeo::EffectHandler::Shutdown();

	Eegeo_DELETE m_pAndroidPlatformAbstractionModule;
	m_pAndroidPlatformAbstractionModule = NULL;

	Eegeo_DELETE m_pJpegLoader;
	m_pJpegLoader = NULL;

	Eegeo_DELETE m_pScreenProperties;
	m_pScreenProperties = NULL;

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

	m_uiToNativeMessageBus.Flush();

	m_pApp->Update(dt);

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

	m_nativeToUiMessageBus.Flush();

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

	// 3d map view layer.
	m_pWorldPinOnMapViewModule = Eegeo_NEW(ExampleApp::WorldPins::WorldPinOnMapViewModule)(
	                                     m_nativeState,
	                                     app.WorldPinsModule().GetWorldPinInFocusViewModel(),
	                                     app.WorldPinsModule().GetScreenControlViewModel(),
	                                     app.PinDiameter()
	                                 );

	// HUD behind modal background layer.
	m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::FlattenButtonViewModule)(
	                                 m_nativeState,
	                                 app.FlattenButtonModule().GetFlattenButtonViewModel(),
	                                 m_uiToNativeMessageBus,
	                                 m_nativeToUiMessageBus
	                             );

	m_pMyPinCreationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::MyPinCreationViewModule)(
									m_nativeState,
									app.MyPinCreationModule().GetMyPinCreationModel(),
									app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
									app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
									app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
									m_uiToNativeMessageBus
								);


	m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::CompassViewModule)(
	                           m_nativeState,
	                           app.CompassModule().GetCompassViewModel(),
	                           m_uiToNativeMessageBus,
	                           m_nativeToUiMessageBus
	                       );

	// Modal background layer.
	m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::ModalBackgroundViewModule)(
	                                   m_nativeState,
	                                   app.ModalityModule().GetModalityModel()
	                               );

	// Menus & HUD layer.
	m_pPrimaryMenuViewModule = Eegeo_NEW(ExampleApp::Menu::MenuViewModule)(
	                               "com/eegeo/primarymenu/PrimaryMenuView",
	                               m_nativeState,
	                               app.PrimaryMenuModule().GetPrimaryMenuModel(),
	                               app.PrimaryMenuModule().GetPrimaryMenuViewModel()
	                           );

	m_pSecondaryMenuViewModule = Eegeo_NEW(ExampleApp::SecondaryMenu::SecondaryMenuViewModule)(
	                                 "com/eegeo/secondarymenu/SecondaryMenuView",
	                                 m_nativeState,
	                                 app.SecondaryMenuModule().GetSecondaryMenuModel(),
	                                 app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
	                                 m_uiToNativeMessageBus,
	                                 m_nativeToUiMessageBus
	                             );

	m_pSearchResultMenuViewModule = Eegeo_NEW(ExampleApp::SearchMenu::SearchMenuViewModule)(
	                                    "com/eegeo/searchmenu/SearchMenuView",
	                                    m_nativeState,
	                                    app.SearchResultMenuModule().GetSearchResultMenuModel(),
	                                    app.SearchResultMenuModule().GetMenuViewModel(),
	                                    app.CategorySearchModule().GetCategorySearchRepository(),
	                                    app.SearchResultMenuModule().GetSearchResultMenuViewModel(),
	                                    m_uiToNativeMessageBus,
	                                    m_nativeToUiMessageBus
	                                );

	// Pop-up layer.
	m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::SearchResultPoiViewModule)(
	                                   m_nativeState,
	                                   app.SearchResultPoiModule().GetSearchResultPoiViewModel()
	                               );

	m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::AboutPageViewModule)(
	                             m_nativeState,
	                             app.AboutPageModule().GetAboutPageModel(),
	                             app.AboutPageModule().GetAboutPageViewModel()
	                         );

	m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewModule)(
								m_nativeState,
								app.MyPinCreationModule().GetMyPinCreationModel(),
								app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
								m_uiToNativeMessageBus
							);

	m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::ViewControllerUpdaterModule);

	ExampleApp::ViewControllerUpdater::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();

	viewControllerUpdaterModel.AddUpdateableObject(m_pPrimaryMenuViewModule->GetMenuViewController());
	viewControllerUpdaterModel.AddUpdateableObject(m_pSecondaryMenuViewModule->GetMenuViewController());
	viewControllerUpdaterModel.AddUpdateableObject(m_pSearchResultMenuViewModule->GetMenuViewController());
}

void AppHost::DestroyApplicationViewModulesFromUiThread()
{
	ASSERT_UI_THREAD

	if(m_createdUIModules)
	{
		Eegeo_DELETE m_pViewControllerUpdaterModule;

		Eegeo_DELETE m_pMyPinCreationDetailsViewModule;

		Eegeo_DELETE m_pFlattenButtonViewModule;

		Eegeo_DELETE m_pMyPinCreationViewModule;

		Eegeo_DELETE m_pAboutPageViewModule;

		Eegeo_DELETE m_pWorldPinOnMapViewModule;

		Eegeo_DELETE m_pSearchResultPoiViewModule;

		Eegeo_DELETE m_pModalBackgroundViewModule;

		Eegeo_DELETE m_pSearchResultMenuViewModule;

		Eegeo_DELETE m_pSecondaryMenuViewModule;

		Eegeo_DELETE m_pPrimaryMenuViewModule;

		Eegeo_DELETE m_pCompassViewModule;
	}
	m_createdUIModules = false;
}


