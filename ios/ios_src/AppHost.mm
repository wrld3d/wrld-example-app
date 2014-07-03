// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "App.h"
#include "AppHost.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "RenderContext.h"
#include "GlobalLighting.h"
#include "GlobalFogging.h"
#include "AppInterface.h"
#include "Blitter.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "LoadingScreen.h"
#include "PlatformConfig.h"
#include "iOSPlatformConfigBuilder.h"
#include "EegeoWorld.h"
#include "EnvironmentFlatteningService.h"
#include "RouteMatchingExampleFactory.h"
#include "RouteSimulationExampleFactory.h"

using namespace Eegeo::iOS;

AppHost::AppHost(
                 const std::string& apiKey,
                 ViewController& viewController,
                 float displayWidth,
                 float displayHeight,
                 float deviceDpi,
                 float pixelScale
                 )
    :m_viewController(viewController)
    ,m_pTaskQueue(NULL)
	,m_pEnvironmentFlatteningService(NULL)
	,m_piOSWebLoadRequestFactory(NULL)
	,m_piOSWebRequestService(NULL)
	,m_pBlitter(NULL)
	,m_pTextureLoader(NULL)
	,m_pHttpCache(NULL)
	,m_pFileIO(NULL)
	,m_pLighting(NULL)
	,m_pFogging(NULL)
	,m_pShadowing(NULL)
	,m_pRenderContext(NULL)
	,m_piOSLocationService(NULL)
	,m_piOSUrlEncoder(NULL)
	,m_pWorld(NULL)
	,m_pInterestPointProvider(NULL)
	,m_iOSInputBoxFactory()
	,m_iOSKeyboardInputFactory()
	,m_iOSAlertBoxFactory()
	,m_iOSNativeUIFactories(m_iOSAlertBoxFactory, m_iOSInputBoxFactory, m_iOSKeyboardInputFactory)
	,m_terrainHeightRepository()
	,m_terrainHeightProvider(&m_terrainHeightRepository)
	,m_pApp(NULL)
	,m_pExampleController(NULL)
{
	m_piOSUrlEncoder = new iOSUrlEncoder();
	m_piOSLocationService = new iOSLocationService();

	m_pRenderContext = new Eegeo::Rendering::RenderContext();
	m_pRenderContext->SetScreenDimensions(displayWidth, displayHeight, 1.0f, deviceDpi);

	m_pLighting = new Eegeo::Lighting::GlobalLighting();
	m_pFogging = new Eegeo::Lighting::GlobalFogging();
	m_pShadowing = new Eegeo::Lighting::GlobalShadowing();
	m_pEnvironmentFlatteningService = new Eegeo::Rendering::EnvironmentFlatteningService();
    
	m_pFileIO = new iOSFileIO();
	m_pHttpCache = new iOSHttpCache(*m_pFileIO);
	m_pTextureLoader = new iOSTextureFileLoader(m_pFileIO, m_pRenderContext->GetGLState());

	Eegeo::EffectHandler::Initialise();
	m_pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, *m_pRenderContext);
	m_pBlitter->Initialise();

	m_pTaskQueue = new iOSTaskQueue(10);

	m_piOSWebRequestService = new Eegeo::Web::iOSWebRequestService();

	m_piOSWebLoadRequestFactory = new Eegeo::Web::iOSWebLoadRequestFactory(*m_pHttpCache, *m_piOSWebRequestService);

	m_pInterestPointProvider = new Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider();

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
	Eegeo::Config::PlatformConfig config = Eegeo::iOS::iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore()).Build();

	m_pWorld = new Eegeo::EegeoWorld(
	    apiKey,
	    m_pHttpCache,
	    m_pFileIO,
	    m_pTextureLoader,
	    m_piOSWebLoadRequestFactory,
	    m_pTaskQueue,
	    *m_pRenderContext,
	    m_pLighting,
	    m_pFogging,
	    m_pShadowing,
	    m_piOSLocationService,
	    m_pBlitter,
	    m_piOSUrlEncoder,
	    *m_pInterestPointProvider,
	    m_iOSNativeUIFactories,
	    &m_terrainHeightRepository,
	    &m_terrainHeightProvider,
	    m_pEnvironmentFlatteningService,
	    environmentCharacterSet,
	    config,
	    NULL,
	    "",
	    "Default-Landscape@2x~ipad.png"
	);
    
	m_pRenderContext->GetGLState().InvalidateAll();
    
	ConfigureExamples();
    
	m_pAppInputDelegate = new AppInputDelegate(*m_pApp, m_viewController, displayWidth, displayHeight, pixelScale);
    m_pAppLocationDelegate = new AppLocationDelegate(*m_piOSLocationService);
}

AppHost::~AppHost()
{
    delete m_pAppLocationDelegate;
    m_pAppLocationDelegate = NULL;
    
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

	delete m_piOSUrlEncoder;
	m_piOSUrlEncoder = NULL;

	delete m_piOSLocationService;
	m_piOSLocationService = NULL;

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

	delete m_piOSWebRequestService;
	m_piOSWebRequestService = NULL;

	delete m_piOSWebLoadRequestFactory;
	m_piOSWebLoadRequestFactory = NULL;

	delete m_pEnvironmentFlatteningService;
	m_pEnvironmentFlatteningService = NULL;

	delete m_pTaskQueue;
	m_pTaskQueue = NULL;
}

void AppHost::OnResume()
{
	m_pApp->OnResume();
}

void AppHost::OnPause()
{
	m_pApp->OnPause();
	m_pHttpCache->FlushInMemoryCacheRepresentation();
}

void AppHost::SetViewportOffset(float x, float y)
{
}

void AppHost::Update(float dt)
{
	m_pApp->Update(dt);
    m_piOSWebRequestService->Update();
}

void AppHost::Draw(float dt)
{
	m_pApp->Draw(dt);
}

void AppHost::ConfigureExamples()
{
	m_piOSExampleControllerView = new Examples::iOSExampleControllerView([&m_viewController view]);

	m_pExampleController = new Examples::ExampleController(*m_pWorld, *m_piOSExampleControllerView);
	m_pApp = new ExampleApp(m_pWorld, *m_pInterestPointProvider, *m_pExampleController);

	RegisteriOSSpecificExamples();

	m_piOSExampleControllerView->PopulateExampleList(m_pExampleController->GetExampleNames());

	m_pExampleController->ActivatePrevious();
}

void AppHost::RegisteriOSSpecificExamples()
{
	m_piOSRouteMatchingExampleViewFactory = new Examples::iOSRouteMatchingExampleViewFactory([&m_viewController view]);

	m_pExampleController->RegisterExample(new Examples::RouteMatchingExampleFactory(
	        *m_pWorld,
	        *m_piOSRouteMatchingExampleViewFactory,
	        m_pApp->GetCameraController()));

	m_piOSRouteSimulationExampleViewFactory = new Examples::iOSRouteSimulationExampleViewFactory([&m_viewController view]);

	m_pExampleController->RegisterExample(new Examples::RouteSimulationExampleFactory(
	        *m_pWorld,
	        m_pApp->GetCameraController(),
	        *m_piOSRouteSimulationExampleViewFactory));
}

void AppHost::DestroyExamples()
{
	delete m_piOSRouteMatchingExampleViewFactory;
	delete m_piOSRouteSimulationExampleViewFactory;

	delete m_pExampleController;
	delete m_piOSExampleControllerView;
}





