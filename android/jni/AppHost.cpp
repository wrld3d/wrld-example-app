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
#include "RouteMatchingExampleFactory.h"
#include "RouteSimulationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "PinsWithAttachedJavaUIExampleFactory.h"
#include "PositionJavaPinButtonExampleFactory.h"
#include "ExampleCameraJumpController.h"
#include "ShowJavaPlaceJumpUIExampleFactory.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    const std::string& apiKey,
    AndroidNativeState& nativeState,
    float displayWidth,
    float displayHeight,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
	:m_pEnvironmentFlatteningService(NULL)
	,m_pAndroidWebLoadRequestFactory(NULL)
	,m_pAndroidWebRequestService(NULL)
	,m_pBlitter(NULL)
	,m_pTextureLoader(NULL)
	,m_pHttpCache(NULL)
	,m_pFileIO(NULL)
	,m_pLighting(NULL)
	,m_pFogging(NULL)
	,m_pShadowing(NULL)
	,m_pRenderContext(NULL)
	,m_pAndroidLocationService(NULL)
	,m_pAndroidUrlEncoder(NULL)
	,m_pWorld(NULL)
	,m_pInterestPointProvider(NULL)
	,m_androidInputBoxFactory(&nativeState)
	,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
	,m_androidAlertBoxFactory(&nativeState)
	,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
	,m_terrainHeightRepository()
	,m_terrainHeightProvider(&m_terrainHeightRepository)
	,m_pApp(NULL)
	,m_pExampleController(NULL)
	,m_pInputProcessor(NULL)
	,m_nativeState(nativeState)
{
	Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

	m_pSharedGlContext = new Eegeo::Android::AndroidSharedGlContext(display, resourceBuildShareContext, shareSurface);

	m_pAndroidUrlEncoder = new AndroidUrlEncoder(&nativeState);
	m_pAndroidLocationService = new AndroidLocationService(&nativeState);

	m_pRenderContext = new Eegeo::Rendering::RenderContext();
	m_pRenderContext->SetScreenDimensions(displayWidth, displayHeight, 1.0f, nativeState.deviceDpi);

	m_pLighting = new Eegeo::Lighting::GlobalLighting();
	m_pFogging = new Eegeo::Lighting::GlobalFogging();
	m_pShadowing = new Eegeo::Lighting::GlobalShadowing();
	m_pEnvironmentFlatteningService = new Eegeo::Rendering::EnvironmentFlatteningService();

	std::set<std::string> customApplicationAssetDirectories;
	customApplicationAssetDirectories.insert("load_model_example");
	customApplicationAssetDirectories.insert("pin_over_model_example");
	customApplicationAssetDirectories.insert("pins_example");
	customApplicationAssetDirectories.insert("pins_with_attached_java_ui_example");
	customApplicationAssetDirectories.insert("pod_animation_example");
	customApplicationAssetDirectories.insert("route_simulation_example");
	customApplicationAssetDirectories.insert("route_simulation_animation_example");
	m_pFileIO = new AndroidFileIO(&nativeState, customApplicationAssetDirectories);

	m_pHttpCache = new Cache::AndroidHttpCache(*m_pFileIO);
	m_pTextureLoader = new AndroidTextureFileLoader(m_pFileIO, m_pRenderContext->GetGLState());

	Eegeo::EffectHandler::Initialise();
	m_pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, *m_pRenderContext);
	m_pBlitter->Initialise();

	const int webLoadPoolSize = 10;
	const int cacheLoadPoolSize = 40;
	const int cacheStorePoolSize = 20;
	m_pAndroidWebRequestService = new AndroidWebRequestService(*m_pFileIO, m_pHttpCache, webLoadPoolSize, cacheLoadPoolSize, cacheStorePoolSize);

	m_pAndroidWebLoadRequestFactory = new AndroidWebLoadRequestFactory(m_pAndroidWebRequestService, m_pHttpCache);

	m_pInterestPointProvider = new Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider();

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
	std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
	Eegeo::Config::PlatformConfig config = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	m_pWorld = new Eegeo::EegeoWorld(
	    apiKey,
	    *m_pHttpCache,
	    *m_pFileIO,
	    *m_pTextureLoader,
	    *m_pAndroidWebLoadRequestFactory,
	    *this,
	    *m_pRenderContext,
	    *m_pLighting,
	    *m_pFogging,
	    *m_pShadowing,
	    *m_pAndroidLocationService,
	    *m_pBlitter,
	    *m_pAndroidUrlEncoder,
	    *m_pInterestPointProvider,
	    m_androidNativeUIFactories,
	    m_terrainHeightRepository,
	    m_terrainHeightProvider,
	    *m_pEnvironmentFlatteningService,
	    environmentCharacterSet,
	    config,
	    NULL,
	    "",
	    "Default-Landscape@2x~ipad.png"
	);

	m_pAndroidWebRequestService->SetWorkPool(m_pWorld->GetWorkPool());
	m_pInputProcessor = new Eegeo::Android::Input::AndroidInputProcessor(&m_inputHandler, m_pRenderContext->GetScreenWidth(), m_pRenderContext->GetScreenHeight());

	ConfigureExamples();

	m_pAppInputDelegate = new AppInputDelegate(*m_pApp);
	m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
}

AppHost::~AppHost()
{
	m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

	delete m_pAppInputDelegate;
	m_pAppInputDelegate = NULL;

	DestroyExamples();

	delete m_pApp;
	m_pApp = NULL;

	m_pHttpCache->FlushInMemoryCacheRepresentation();

	delete m_pInterestPointProvider;
	m_pInterestPointProvider = NULL;

	delete m_pWorld;
	m_pWorld = NULL;

	delete m_pAndroidUrlEncoder;
	m_pAndroidUrlEncoder = NULL;

	delete m_pAndroidLocationService;
	m_pAndroidLocationService = NULL;

	delete m_pRenderContext;
	m_pRenderContext = NULL;

	delete m_pShadowing;
	m_pShadowing = NULL;

	delete m_pFogging;
	m_pFogging = NULL;

	delete m_pLighting;
	m_pLighting = NULL;

	delete m_pFileIO;
	m_pFileIO = NULL;

	delete m_pHttpCache;
	m_pHttpCache = NULL;

	delete m_pTextureLoader;
	m_pTextureLoader = NULL;

	Eegeo::EffectHandler::Reset();
	Eegeo::EffectHandler::Shutdown();
	m_pBlitter->Shutdown();
	delete m_pBlitter;
	m_pBlitter = NULL;

	delete m_pAndroidWebRequestService;
	m_pAndroidWebRequestService = NULL;

	delete m_pAndroidWebLoadRequestFactory;
	m_pAndroidWebLoadRequestFactory = NULL;

	delete m_pEnvironmentFlatteningService;
	m_pEnvironmentFlatteningService = NULL;

	delete m_pSharedGlContext;
	m_pSharedGlContext = NULL;
}

void AppHost::OnResume()
{
	m_pHttpCache->ReloadCacheRepresentationFromStorage();
	m_pApp->OnResume();
}

void AppHost::OnPause()
{
	m_pApp->OnPause();
	m_pHttpCache->FlushInMemoryCacheRepresentation();
	m_pAndroidLocationService->StopListening();
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
	m_pSharedGlContext->UpdateSurface(sharedSurface);
}

void AppHost::SetViewportOffset(float x, float y)
{
	m_inputHandler.SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	m_pInputProcessor->HandleInput(event);
}

void AppHost::Update(float dt)
{
	m_pAndroidWebRequestService->Update();
	m_pApp->Update(dt);
}

void AppHost::Draw(float dt)
{
	m_pApp->Draw(dt);
}

void AppHost::ConfigureExamples()
{
	m_pAndroidExampleControllerView = new Examples::AndroidExampleControllerView(m_nativeState);

	m_pExampleController = new Examples::ExampleController(*m_pWorld, *m_pAndroidExampleControllerView);
	m_pApp = new ExampleApp(m_pWorld, *m_pInterestPointProvider, *m_pExampleController);

	RegisterAndroidSpecificExamples();

	m_pAndroidExampleControllerView->PopulateExampleList(m_pExampleController->GetExampleNames());

	m_pExampleController->ActivatePrevious();
}

void AppHost::RegisterAndroidSpecificExamples()
{
	m_pAndroidRouteMatchingExampleViewFactory = new Examples::AndroidRouteMatchingExampleViewFactory(
	    m_nativeState);

	m_pExampleController->RegisterExample(new Examples::RouteMatchingExampleFactory(
	        *m_pWorld,
	        *m_pAndroidRouteMatchingExampleViewFactory,
	        m_pApp->GetCameraController()));

	m_pAndroidRouteSimulationExampleViewFactory = new Examples::AndroidRouteSimulationExampleViewFactory(
	    m_nativeState);

	m_pExampleController->RegisterExample(new Examples::RouteSimulationExampleFactory(
	        *m_pWorld,
	        m_pApp->GetCameraController(),
	        *m_pAndroidRouteSimulationExampleViewFactory));

	m_pExampleController->RegisterExample(new Examples::JavaHudCrossThreadCommunicationExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));
	m_pExampleController->RegisterExample(new Examples::PinsWithAttachedJavaUIExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));
	m_pExampleController->RegisterExample(new Examples::PositionJavaPinButtonExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));

	m_pExampleCameraJumpController = new ExampleCameraJumpController(m_pApp->GetCameraController(), m_pApp->GetTouchController());
	m_pExampleController->RegisterExample(new Examples::ShowJavaPlaceJumpUIExampleFactory(*m_pExampleCameraJumpController, m_pApp->GetCameraController(), m_nativeState));
}

void AppHost::DestroyExamples()
{
	delete m_pExampleCameraJumpController;
	delete m_pAndroidRouteMatchingExampleViewFactory;
	delete m_pAndroidRouteSimulationExampleViewFactory;

	delete m_pExampleController;
	delete m_pAndroidExampleControllerView;
}

Eegeo::Concurrency::Tasks::IGlTaskContext* AppHost::Build()
{
	return m_pSharedGlContext;
}




