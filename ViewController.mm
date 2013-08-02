#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector.h>
#include <sstream>
#include <sys/types.h>
#include <sys/sysctl.h>

#include "ASIHTTPRequest.h"
#include "ViewController.h"
#include "ResourceCache.h"
#include "External/Reachability/Reachability.h"
#include "DebugValues.h"
#include "CameraModel.h"
#include "PrecacheService.h"
#include "NewGlobeCamera.h"
#include "MeshPool.h"
#include "StreamingController.h"
#include "EegeoEnvironmentRendering.h"
#include "MaterialRepository.h"
#include "StencilShadowMaterial.h"
#include "App.h"
#include "AppOnMap.h"
#include "IOSHelper.h"
#include "ChunkedLcmTerrainBuilder.h"
#include "PlaceNamesBuilder.h"
#include "PayloadPool.h"
#include "SummaryStats.h"
#include "BuildingStreaming.h"
#include "TerrainStreaming.h"
#include "PlaceNamesStreaming.h"
#include "RoadStreaming.h"
#include "DefaultMaterialFactory.h"
#include "EnvironmentFlatteningService.h"
#include "Graphics.h"
#include "Camera.h"
#include "EffectHandler.h"
#include "EffectHandler.h"
#include "LatLongAltitude.h"
#include "CameraModel.h"
#include "IAppOnMap.h"
#include "EegeoWorld.h"
#include "Blitter.h"
#include "GLState.h"
#include "RenderContext.h"
#include "GlobalLighting.h"
#include "GlobalFogging.h"
#include "DefaultMaterialFactory.h"
#include "iOSTaskQueue.h"
#include "ResourceCache.h"
#include "iOSFileIO.h"
#include "iOSTextureFileLoader.h"
#include "VehicleModelLoader.h"
#include "VehicleModelRepository.h"
#include "iOSWebLoadRequestFactory.h"
#include "iOSLocationService.h"
#include "iOSUrlEncoder.h"
#include "SearchServiceCredentials.h"
#include "GlobeCameraInterestPointProvider.h"
#include "TerrainHeightProvider.h"

#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"

#define API_KEY "OBTAIN API KEY FROM https://appstore.eegeo.com AND INSERT IT HERE"

//#define USING_SEARCH_EXAMPLE

#if defined(USING_SEARCH_EXAMPLE)
//If you intend to use the SearchService, you must provide SearchServiceCredentials for the
//here.com provider, obtainable at http://developer.here.com/plans
#define HERE_DOT_COM_DEVELOPER_APP_ID ""
#define HERE_DOT_COM_DEVELOPER_APP_CODE ""
Eegeo::Search::Service::SearchServiceCredentials credentials(HERE_DOT_COM_DEVELOPER_APP_ID, HERE_DOT_COM_DEVELOPER_APP_CODE);
Eegeo::Search::Service::SearchServiceCredentials* pCredentials = &credentials;
#else
Eegeo::Search::Service::SearchServiceCredentials* pCredentials = NULL;
#endif


using namespace Eegeo::iOS;

iOSUrlEncoder iOSUrlEncoder;

@interface ViewController()
{
    
}


@property (strong, nonatomic) EAGLContext *context;
@end


@implementation ViewController

CLLocationManager *locationManager;
CFTimeInterval previousTimestamp = CFAbsoluteTimeGetCurrent();
CFTimeInterval smoothedFrameDuration = 0.1;
CFTimeInterval debugStatsUpdateExpiry = 0;
int framesForAvgFps = 0;
CFTimeInterval avgFpsStartTime = CFAbsoluteTimeGetCurrent();

@synthesize fps;
@synthesize avgfps;
@synthesize smoothedFrameTime;
@synthesize mem;
@synthesize terrains;
@synthesize buildings;
@synthesize models;
@synthesize camera;
@synthesize payloads;
@synthesize renderData;

@synthesize resetCounters;
@synthesize toggleCollapse;
@synthesize debug;
@synthesize clearCache;
@synthesize precacheVolume;
@synthesize precacheVolumeProgress;
@synthesize streamingEnabled;

//debug places
@synthesize places;
@synthesize sf;
@synthesize ldn;
@synthesize ny;
@synthesize chic;
@synthesize la;
@synthesize edin;
@synthesize glasgow;
@synthesize sandiego;
@synthesize cambridge;
@synthesize oban;
@synthesize barcelona;
@synthesize kyoto;

//resource data
@synthesize resBtnBuildings;
@synthesize resBtnLandmarks;
@synthesize resBtnLcm;
@synthesize resBtnModels;
@synthesize resBtnPlacenames;
@synthesize resBtnRoads;
@synthesize resBtnShadows;
@synthesize resTxtTotalsForAllRes;
@synthesize resTxtNumResourcesRequested;
@synthesize resTxtTotalBytesLoaded;
@synthesize resTxtBytesLoadedFromCacheAndWeb;
@synthesize resTxtAvgBytesPerSuccessLoad;
@synthesize resTxtTotalByRequestOutcome;
@synthesize resTxtAvgBuild;
@synthesize resTxtAvgLoadTimes;

namespace DebuggedResource
{
    enum ResourceType
    {
        Buildings=0,
        Terrain,
        Placenames,
        Roads,
        NumResources,
        //this ordering is deliberate as "models" is an aggregate stream so must be treated differently
        Models,
        None
        
    };
}

float pixelScale = 1.0f;
bool menuHidden = false;
std::vector<Eegeo::Streaming::LoggingResourceStream*> streams;
DebuggedResource::ResourceType currentDebuggedResource = DebuggedResource::None;
UIButton* currentDebuggedResourceButton = NULL;
NSTimer* touchTimer;
Eegeo::Location::GlobeCameraInterestPointProvider* m_pInterestPointProvider;
iOSLocationService* piOSLocationService = NULL;
Eegeo::Resources::Terrain::Heights::TerrainHeightRepository m_terrainHeightRepository;
Eegeo::Resources::Terrain::Heights::TerrainHeightProvider m_terrainHeightProvider(&m_terrainHeightRepository);

Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory inputBoxFactory;
Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory keyboardInputFactory;
Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory alertBoxFactory;
Eegeo::UI::NativeUIFactories nativeUIFactories(alertBoxFactory, inputBoxFactory, keyboardInputFactory);

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)dealloc {
    [super dealloc];
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)viewDidUnload
{
    [super viewDidUnload];
    
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
	self.context = nil;
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = self;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    [locationManager startUpdatingLocation];
    
    [self initInputs];
    [self initGraphics];
    [self initWorld];
    [self initHUD];
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    myApp->Draw(1.0f/60.0f);
    
    const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
    Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)update
{
    CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
    CFTimeInterval frameDuration = timeNow - previousTimestamp;
    
    // Update the game.
    myApp->Update(frameDuration);
    
    self.preferredFramesPerSecond = 60.0f;
    //////////
    
    ++framesForAvgFps;
    
    smoothedFrameDuration += (frameDuration - smoothedFrameDuration)*0.03;
    previousTimestamp = timeNow;
    
    if(precaching)
    {
        const Eegeo::Web::PrecacheService& precachingService = myApp->World().GetPrecachingService();
        [precacheVolumeProgress setProgress: (precachingService.UrlsLoaded()/(float)precachingService.TotalUrlsToLoad())];
        if(!precachingService.CurrentlyPrecaching())
        {
            precaching = false;
            [precacheVolume setAlpha: 1.0f];
            [precacheVolume setEnabled: true];
        }
    }
    
    if (timeNow < debugStatsUpdateExpiry)
    {
        return;
    }

    [self updateDebugHUD :timeNow];
}


- (void)updateDebugHUD:(CFTimeInterval)timeNow
{
    const float debugUpdateIntervalSeconds = 1.0f;
    debugStatsUpdateExpiry = timeNow + debugUpdateIntervalSeconds;
    
    std::stringstream ss_fps;
    ss_fps << "FPS:: " << (1.0/smoothedFrameDuration);
    fps.text = [NSString stringWithUTF8String:ss_fps.str().c_str()];
    
    std::stringstream ss_smoothedFrameTime;
    ss_smoothedFrameTime << "FT: " << (smoothedFrameDuration*1000.0) << "ms";
    smoothedFrameTime.text = [NSString stringWithUTF8String:ss_smoothedFrameTime.str().c_str()];
    
    std::stringstream ss_avgfps;
    ss_avgfps << "Avg FPS: " << (framesForAvgFps/(timeNow - avgFpsStartTime));
    avgfps.text = [NSString stringWithUTF8String:ss_avgfps.str().c_str()];
    
    std::stringstream ss_mem;
    ss_mem << "Mem:: used: " << IOSHelper::GetTaskTotalMemoryUsageInBytes() << " B; vm "
    << IOSHelper::GetTaskVirtualMemoryUsageInBytes()/1000 << " kB; free "
    << IOSHelper::GetFreeMemoryInBytes()/1000 << " kB";
    mem.text = [NSString stringWithUTF8String:ss_mem.str().c_str()];
    
    std::stringstream ss_terrains;
    Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& terrainPool = myApp->World().GetTerrainMeshPool();
    ss_terrains << "Terrains:: " << terrainPool.GetCount() << "/" <<  terrainPool.GetCapacity();
    terrains.text = [NSString stringWithUTF8String:ss_terrains.str().c_str()];
    
    std::stringstream ss_buildings;
    Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool = myApp->World().GetBuildingMeshPool();
    ss_buildings << "Buildings:: " << buildingPool.GetCount() << "/" <<  buildingPool.GetCapacity();
    buildings.text = [NSString stringWithUTF8String:ss_buildings.str().c_str()];
    
    float meanTimeWaitingToBeQueuedHttp = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::TO_BE_LOADED, false)->mean();
    float meanTimeQueuedForLoadingHttp = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::QUEUED_FOR_LOADING, false)->mean();
    float meanTimeToLoadHttp = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::LOADING, false)->mean();
    float meanTimeWaitingToBeQueuedCache = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::TO_BE_LOADED, true)->mean();
    float meanTimeQueuedForLoadingCache = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::QUEUED_FOR_LOADING, true)->mean();
    float meanTimeToLoadCache = myApp->World().GetPayloadPool().stateTimeStats(Eegeo::PayloadState::LOADING, true)->mean();
    
    std::stringstream ss_payloads;
    ss_payloads << "Payloads:: "
    << Eegeo::Debug::DebugValues::numPayloadsToLoad << " waiting to ld, "
    << Eegeo::Debug::DebugValues::numPayloadsQueuedForLoading << " lding, "
    << Eegeo::Debug::DebugValues::numPayloadsFailedLoad << " failed ld, "
    << Eegeo::Debug::DebugValues::numPayloadsToBuild << " waiting to bld, "
    << (int)(meanTimeWaitingToBeQueuedHttp*1000) << "ms mean pre queue http, "
    << (int)(meanTimeQueuedForLoadingHttp*1000) << "ms mean ld queue http, "
    << (int)(meanTimeToLoadHttp*1000) << "ms mean lding http, "
    << (int)(meanTimeWaitingToBeQueuedCache*1000) << "ms mean pre queue cache, "
    << (int)(meanTimeQueuedForLoadingCache*1000) << "ms mean ld queue cache, "
    << (int)(meanTimeToLoadCache*1000) << "ms mean lding cache"
    ;
    payloads.text = [NSString stringWithUTF8String:ss_payloads.str().c_str()];
    
    float rot = myApp->pGlobeCamera->CurrentRotationRadians();
    rot = fmodf(Eegeo::Math::Rad2Deg(rot), 360.0f);
    if(rot < 0.0f) rot = 360.0f + rot;
    
    Eegeo::Space::LatLongAltitude interestPoint = Eegeo::Space::LatLongAltitude::FromECEF(myApp->pGlobeCamera->GetInterestPointECEF());
    Eegeo::Space::LatLongAltitude eyePoint = Eegeo::Space::LatLongAltitude::FromECEF(myApp->World().GetCameraModel().GetWorldPosition());
    char cameraParams[200];
    sprintf (
             cameraParams,
             "Lat=%0.6f Long=%0.6f, Alt=%0.4f, Rot=%0.4f",
             interestPoint.GetLatitudeInDegrees(),
             interestPoint.GetLongitudeInDegrees(),
             eyePoint.GetAltitude(),
             rot
             );
    camera.text = [NSString stringWithUTF8String:cameraParams];
    
    std::stringstream ss_renderdata;
    ss_renderdata << "Polys :: " << Eegeo::Debug::DebugValues::totalPolysRendered << ", Shadow Polys ::" << Eegeo::Debug::DebugValues::shadowPolysRendered << ", Batches :: " << Eegeo::Debug::DebugValues::totalDrawCalls << ", ShadowDraw :: " << Eegeo::Debug::DebugValues::totalShadowDrawCalls;
    renderData.text = [NSString stringWithUTF8String:ss_renderdata.str().c_str()];
    
    [self printResourceStats];
}


-(void)clearCacheToggleButtonPressedHandler {
    [ResourceCache clearCache];
}

-(void)wireframeBuildingsToggleButtonPressedHandler {
    Eegeo::EegeoEnvironmentRendering& rendering = myApp->World().GetEnvironmentRendering();
    Eegeo::Rendering::MaterialRepository<Eegeo::Rendering::Material>& materials = *rendering.Materials();
    Eegeo::Rendering::StencilShadowMaterial& shadow = ((Eegeo::Rendering::StencilShadowMaterial&)*materials.GetMaterial("stencil_shadow"));
    shadow.ToggleWireframe();
}

-(void)streamingToggleButtonPressedHandler {
    Eegeo::Streaming::StreamingController& streaming = myApp->World().GetStreamingController();
    streaming.SetEnabled(!streaming.Enabled());
}

-(void)toggleCollapseButtonPressedHandler {
    myApp->World().GetEnvironmentFlatteningService().ToggleFlattened();
}

-(void)resetCountersButtonPressedHandler {
    myApp->World().GetBuildingBuilder().ResetCounters();
    myApp->World().GetLcmTerrainBuilder().ResetCounters();
    myApp->World().GetPlaceNamesBuilder().ResetCounters();
    myApp->World().GetRoadBuilder().ResetCounters();
    
    for(std::vector<Eegeo::Streaming::LoggingResourceStream*>::iterator it = streams.begin(); it != streams.end(); ++ it)
    {
        (*it)->ResetCounters();
    }
    
    myApp->World().GetPayloadPool().ResetStats();
    framesForAvgFps = 0;
    avgFpsStartTime = CFAbsoluteTimeGetCurrent();
}


- (void) initInputs
{
    // Make sure multi-touch is working.
    [self.view setMultipleTouchEnabled: true];
    
    gestureRotation = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(gestureRotation_Callback:)];
    
    [gestureRotation setDelegate:self];
    gestureRotation.cancelsTouchesInView = FALSE;
    [self.view addGestureRecognizer: gestureRotation];
    [gestureRotation release];
    
    gesturePinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(gesturePinch_Callback:)];
    
    [gesturePinch setDelegate:self];
    gesturePinch.cancelsTouchesInView = FALSE;
    [self.view addGestureRecognizer: gesturePinch];
    [gesturePinch release];
    
    
    gesturePan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(gesturePan_Callback:)];
    
    [gesturePan setDelegate:self];
    gesturePan.cancelsTouchesInView = FALSE;
    [self.view addGestureRecognizer: gesturePan];
    [gesturePan release];
    
    
    gestureTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gestureTap_Callback:)];
    
    [gestureTap setDelegate:self];
    gestureTap.cancelsTouchesInView = FALSE;
    [self.view addGestureRecognizer: gestureTap];
    [gestureTap release];
    
    
    gestureDoubleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gestureDoubleTap_Callback:)];
    
    [gestureDoubleTap setDelegate:self];
    gestureDoubleTap.cancelsTouchesInView = FALSE;
	gestureDoubleTap.delaysTouchesEnded = FALSE;
	gestureDoubleTap.numberOfTapsRequired = 2;
    [self.view addGestureRecognizer: gestureDoubleTap];
    [gestureDoubleTap release];
    
    
    gesturePress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(gesturePress_Callback:)];
    
    [gesturePress setDelegate:self];
    gesturePress.cancelsTouchesInView = FALSE;
    [self.view addGestureRecognizer: gesturePress];
    [gesturePress release];
}

- (void) initGraphics
{
    // Init Device
    u32 uTargetFPS;
    
    u32 uDevice = App::GetDevice();
    
    if (uDevice == GAME_DEVICE_IPAD2 ||
        uDevice == GAME_DEVICE_IPHONE4S)
    {
        uTargetFPS = 30.0f;
    }
    else
    {
        uTargetFPS = 30.0f;
    }
    
    NSLog(@"Target FPS: %d", uTargetFPS);
    
    self.preferredFramesPerSecond = uTargetFPS;
    
	App::Initialise();
    
    GLKViewDrawableMultisample multiSample;
    
    if ((App::GetDevice() == GAME_DEVICE_IPAD2) ||
		(App::GetDevice() == GAME_DEVICE_IPAD3))
    {
        multiSample = GLKViewDrawableMultisample4X;
    }
    else
    {
		multiSample = GLKViewDrawableMultisampleNone;
	}
	
    GLKView* view = (GLKView*)((UIViewController*)self).view;
    
    // Create an OpenGLES2 context and store.
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (view.context == nil)
    {
        NSLog(@"Graphics(): Error - Failed to create ES context");
    }
    
    // Set the default values for the screen, depth and stencil buffers.
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    view.drawableMultisample = multiSample;
    
    [EAGLContext setCurrentContext: view.context];
    
	// Get the pixel scale to account for retina displays...
	UIScreen* screen = [UIScreen mainScreen];
	if ([screen respondsToSelector: @selector(scale)])
	{
		pixelScale = screen.scale;
	}
	else
	{
		pixelScale = 1.f;
	}
    
    float width 		= view.bounds.size.width * pixelScale;
    float height 		= view.bounds.size.height * pixelScale;
    
	bool boPortrait = App::IsDeviceSmall();
	
    if (!boPortrait) {
        float temp = width;
        width = height;
        height = temp;
    }
    
    m_renderContext = new Eegeo::Rendering::RenderContext();
    m_renderContext->SetScreenDimensions(width, height, pixelScale);
}

- (void) initWorld
{
    Eegeo::EffectHandler::Initialise();
    Eegeo::RenderCamera* pRenderCamera = new Eegeo::RenderCamera();
    Eegeo::Camera::CameraModel*  pCameraModel = new Eegeo::Camera::CameraModel(pRenderCamera);
    Eegeo::Camera::NewGlobeCamera* cameraController = new Eegeo::Camera::NewGlobeCamera(pCameraModel, pRenderCamera, m_terrainHeightProvider);
    
    piOSLocationService = new iOSLocationService;

    myApp = new ::MyApp(cameraController);
    
    pRenderCamera->SetViewport(0.f, 0.f, m_renderContext->GetScreenWidth(), m_renderContext->GetScreenHeight());
    
    m_pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, *m_renderContext);
    m_pBlitter->Initialise();
    
    Eegeo::Lighting::GlobalLighting* pLighting = new Eegeo::Lighting::GlobalLighting();
    Eegeo::Lighting::GlobalFogging* pFogging = new Eegeo::Lighting::GlobalFogging();
    
    iOSFileIO* p_iOSFileIO = new iOSFileIO();
    Eegeo::Helpers::IFileIO* pFileIO = p_iOSFileIO;
    Eegeo::Helpers::ITextureFileLoader* pTextureFileLoader = new iOSTextureFileLoader(p_iOSFileIO, m_renderContext->GetGLState());
    iOSHttpCache* p_iOSHttpCache = new iOSHttpCache(*p_iOSFileIO);
    Eegeo::Helpers::IHttpCache* pHttpCache = p_iOSHttpCache;
    Eegeo::Web::IWebLoadRequestFactory* pPayloadRequestFactory = new Eegeo::Web::iOSWebLoadRequestFactory(*p_iOSHttpCache);
    Eegeo::Helpers::ITaskQueue* pTaskQueue = new iOSTaskQueue(10);
    
    Eegeo::Rendering::IMaterialFactory* pMaterialFactory = new Eegeo::Rendering::DefaultMaterialFactory();
    pMaterialFactory->Initialise(m_renderContext, pLighting, pFogging, m_pBlitter, pFileIO, pTextureFileLoader);
    
    Eegeo::Traffic::VehicleModelRepository* pVehicleModelRepository = new Eegeo::Traffic::VehicleModelRepository;
    Eegeo::Traffic::VehicleModelLoader* pVehicleModelLoader = new Eegeo::Traffic::VehicleModelLoader(m_renderContext->GetGLState(),
                                                                                                     *pTextureFileLoader,
                                                                                                     *pFileIO);
   
    Eegeo::Traffic::VehicleModelLoaderHelper::LoadAllVehicleResourcesIntoRepository(*pVehicleModelLoader, *pVehicleModelRepository);
    
    m_pInterestPointProvider = Eegeo_NEW(Eegeo::Location::GlobeCameraInterestPointProvider(*cameraController));
    
    myApp->Start(new Eegeo::EegeoWorld(API_KEY,
                                       pHttpCache,
                                       pFileIO,
                                       pTextureFileLoader,
                                       pPayloadRequestFactory,
                                       pTaskQueue,
                                       pVehicleModelRepository,
                                       *m_renderContext,
                                       pCameraModel,
                                       cameraController,
                                       pLighting,
                                       pFogging,
                                       pMaterialFactory,
                                       piOSLocationService,
                                       m_pBlitter,
                                       &iOSUrlEncoder,
                                       *m_pInterestPointProvider,
                                       nativeUIFactories,
                                       &m_terrainHeightRepository,
                                       &m_terrainHeightProvider,
                                       pCredentials
                                       ));
    
    m_renderContext->GetGLState().InvalidateAll();
}

- (void) initHUD
{
    precaching = false;
    [precacheVolumeProgress setProgress:0.0f];
    
	[fps setHidden:false];
    [smoothedFrameTime setHidden:false];
	[mem setHidden:false];
    
    [clearCache setTitle:@"Clear Cache" forState:UIControlStateNormal];
    [clearCache addTarget:self action:@selector(clearCacheToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    
    [wireframeBuildings setTitle:@"Wireframe Shadows" forState:UIControlStateNormal];
    [wireframeBuildings addTarget:self action:@selector(wireframeBuildingsToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    
    [streamingEnabled setTitle:@"Toggle Streaming" forState:UIControlStateNormal];
    [streamingEnabled addTarget:self action:@selector(streamingToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    
    [debug setTitle:@"Debug!" forState:UIControlStateNormal];
    [debug addTarget:self action:@selector(debugControlsToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    
    [resetCounters addTarget:self action:@selector(resetCountersButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    [toggleCollapse addTarget:self action:@selector(toggleCollapseButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    
    [self debugControlsToggleButtonPressedHandler];
    
    //debug places
    [places addTarget:self action:@selector(debugPlacesToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    [sf addTarget:self action:@selector(goToSf) forControlEvents:UIControlEventTouchUpInside];
    [ldn addTarget:self action:@selector(goToLdn) forControlEvents:UIControlEventTouchUpInside];
    [ny addTarget:self action:@selector(goToNy) forControlEvents:UIControlEventTouchUpInside];
    [chic addTarget:self action:@selector(goToChicago) forControlEvents:UIControlEventTouchUpInside];
    [la addTarget:self action:@selector(goToLa) forControlEvents:UIControlEventTouchUpInside];
    [edin addTarget:self action:@selector(goToEdinburgh) forControlEvents:UIControlEventTouchUpInside];
    [glasgow addTarget:self action:@selector(goToGlasgow) forControlEvents:UIControlEventTouchUpInside];
    [sandiego addTarget:self action:@selector(goToSanDiego) forControlEvents:UIControlEventTouchUpInside];
    [cambridge addTarget:self action:@selector(goToCambridge) forControlEvents:UIControlEventTouchUpInside];
    [oban addTarget:self action:@selector(goToOban) forControlEvents:UIControlEventTouchUpInside];
    [barcelona addTarget:self action:@selector(goToBarcelona) forControlEvents:UIControlEventTouchUpInside];
    [kyoto addTarget:self action:@selector(goToKyoto) forControlEvents:UIControlEventTouchUpInside];
    [precacheVolume addTarget:self action:@selector(beginPrecacheVolume) forControlEvents:UIControlEventTouchUpInside];
    
    [self debugPlacesToggleButtonPressedHandler];
    
    //resources
    [resBtnBuildings addTarget:self action:@selector(toggleBuildingResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnLandmarks addTarget:self action:@selector(toggleLandmarkResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnLcm addTarget:self action:@selector(toggleLcmResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnModels addTarget:self action:@selector(toggleModelResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnPlacenames addTarget:self action:@selector(togglePlaceNamesResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnRoads addTarget:self action:@selector(toggleRoadsResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    [resBtnShadows addTarget:self action:@selector(toggleShadowsResourceDebugInfo) forControlEvents:UIControlEventTouchUpInside];
    
    streams.resize(DebuggedResource::NumResources);
    streams[DebuggedResource::Buildings] = (&myApp->World().GetBuildingStreaming());
    streams[DebuggedResource::Terrain] = (&myApp->World().GetTerrainStreaming());
    streams[DebuggedResource::Placenames] = (&myApp->World().GetPlaceNamesStreaming());
    streams[DebuggedResource::Roads] = (&myApp->World().GetRoadStreaming());
}

-(void)debugControlsToggleButtonPressedHandler {
    menuHidden = !menuHidden;
    
	[fps setHidden: menuHidden];
    [avgfps setHidden: menuHidden];
    [smoothedFrameTime setHidden: menuHidden];
	[mem setHidden: menuHidden];
	[terrains setHidden: menuHidden];
	[buildings setHidden: menuHidden];
	[renderData setHidden: menuHidden];
	[models setHidden: menuHidden];
	[camera setHidden: menuHidden];
	[clearCache setHidden: menuHidden];
	[wireframeBuildings setHidden: menuHidden];
	[streamingEnabled setHidden: menuHidden];
    [payloads setHidden: menuHidden];
    [precacheVolume setHidden: menuHidden];
    [precacheVolumeProgress setHidden: menuHidden];
    [toggleCollapse setHidden: menuHidden];
    
    [resTxtTotalsForAllRes setHidden: menuHidden];
    
    [resetCounters setHidden: menuHidden];
    [resBtnBuildings setHidden: menuHidden];
    [resBtnLandmarks setHidden: menuHidden];
    [resBtnLcm setHidden: menuHidden];
    [resBtnModels setHidden: menuHidden];
    [resBtnPlacenames setHidden: menuHidden];
    [resBtnRoads setHidden: menuHidden];
    [resBtnShadows setHidden: menuHidden];
    
    bool debuggingResources = currentDebuggedResource != DebuggedResource::None;
    bool shouldHide = !debuggingResources || menuHidden;
    [self toggleResourcesDebugItemsHidden :shouldHide];
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gestureRotation_Callback:(UIRotationGestureRecognizer*)recognizer
{
	AppInterface::RotateData data;
	
	data.rotation	= recognizer.rotation;
	data.numTouches	= recognizer.numberOfTouches;
	
    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        myApp->Event_TouchRotate_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        myApp->Event_TouchRotate (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        myApp->Event_TouchRotate_End (data);
    }
    
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gesturePinch_Callback:(UIPinchGestureRecognizer*)recognizer
{
    float dist;
    static bool reset = true;
    
    if (recognizer.numberOfTouches == 2)
    {
        {
            CGPoint point0 = [recognizer locationOfTouch:0 inView:self.view];
            CGPoint point1 = [recognizer locationOfTouch:1 inView:self.view];
            
            // Distance between two points.
            Eegeo::v2 p0(point0.x, point0.y);
            Eegeo::v2 p1(point1.x, point1.y);
			
			Eegeo::v2 v2Dist = Eegeo::v2::Sub(p0, p1);
            
            dist = v2Dist.Length();
            
            if (reset)
            {
                _previousDist = dist;
                reset = false;
            }
        }
        
    }
    else
    {
        dist = _previousDist;
        reset = true;
    }
    
	AppInterface::PinchData data;
    
    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        _previousDist = dist;
		
		data.scale	= 0.0f;
        myApp->Event_TouchPinch_Start(data);
        
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        float delta = (_previousDist-dist);
        float majorScreenDimension = fmaxf(m_renderContext->GetScreenHeight(), m_renderContext->GetScreenWidth());
		data.scale = delta/majorScreenDimension;
        myApp->Event_TouchPinch (data);
        _previousDist = dist;
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
		data.scale	= recognizer.scale;
        myApp->Event_TouchPinch_End (data);
    }
    
    _previousDist = dist;
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gesturePan_Callback:(UIPanGestureRecognizer*)recognizer
{
    CGPoint position = [recognizer translationInView:self.view];
	CGPoint positionAbs = [recognizer locationInView:self.view];
    CGPoint velocity = [recognizer velocityInView:self.view];
    
	positionAbs.x *= pixelScale;
	positionAbs.y *= pixelScale;
    
	AppInterface::PanData data;
	
	data.pointRelative	= *(Eegeo::v2*)&position;
    float majorScreenDimension = fmaxf(m_renderContext->GetScreenHeight(), m_renderContext->GetScreenWidth());
    data.pointRelativeNormalized = (data.pointRelative)/majorScreenDimension;
	data.pointAbsolute	= *(Eegeo::v2*)&positionAbs;
	data.velocity	= *(Eegeo::v2*)&velocity;
	
    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        myApp->Event_TouchPan_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        myApp->Event_TouchPan (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        myApp->Event_TouchPan_End (data);
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gestureTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:self.view];
        
		position.x *= pixelScale;
		position.y *= pixelScale;
		
		AppInterface::TapData data;
		
		data.point	= *(Eegeo::v2*)&position;
        
        myApp->Event_TouchTap (data);
        
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gestureDoubleTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:self.view];
		
		position.x *= pixelScale;
		position.y *= pixelScale;
        
		AppInterface::TapData data;
		
		data.point	= *(Eegeo::v2*)&position;
        
        myApp->Event_TouchDoubleTap (data);
        
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void)gesturePress_Callback:(UILongPressGestureRecognizer*)recognizer
{
	AppInterface::TouchHeldData data;
	
	CGPoint position = [recognizer locationInView:self.view];
	
    position.x *= pixelScale;
    position.y *= pixelScale;
    
	data.point	= *(Eegeo::v2*)&position;
	
    /*  if (recognizer.state == UIGestureRecognizerStateBegan)
     {
     myApp->Event_TouchHeld_Start (data);
     }
     else if (recognizer.state == UIGestureRecognizerStateChanged)
     {
     myApp->Event_TouchHeld_Move (data);
     }
     else if (recognizer.state == UIGestureRecognizerStateEnded)
     {
     myApp->Event_TouchHeld_End (data);
     }*/
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([touches count]>0)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:0];
        CGPoint position = [touch locationInView: self.view];
        
		position.x *= pixelScale;
		position.y *= pixelScale;
        
		AppInterface::TouchData data;
		data.point	= *(Eegeo::v2*)&position;
        
        myApp->Event_TouchDown (data);
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([touches count]>0)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:0];
        CGPoint position = [touch locationInView: self.view];
        
		position.x *= pixelScale;
		position.y *= pixelScale;
        
		AppInterface::TouchData data;
		data.point	= *(Eegeo::v2*)&position;
        
        myApp->Event_TouchMove (data);
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
-(void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([touches count]>0)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:0];
        CGPoint position = [touch locationInView: self.view];
        
		position.x *= pixelScale;
		position.y *= pixelScale;
        
		AppInterface::TouchData data;
		data.point	= *(Eegeo::v2*)&position;
        
        myApp->Event_TouchUp (data);
    }
    
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}


-(void)beginPrecacheVolume {
    Eegeo::Streaming::IStreamingVolume& volume = myApp->World().GetStreamingVolume();
    myApp->World().GetPrecachingService().Precache(volume);
    precaching = true;
    [precacheVolume setEnabled: false];
    [precacheVolume setAlpha: 0.6f];
}

-(void)goToSf {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(37.7858,-122.401, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    0.0f,
                                                    1781.0f);
}

-(void)goToLdn {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(51.506172,-0.118915, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    351.0f,
                                                    2731.0f);
}

-(void)goToSanDiego {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(32.707806,-117.167137, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    25.0f,
                                                    2000.0f);
}

-(void)goToNy {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(40.703762, -74.013733, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    240.0f,
                                                    1800.0f);
}

-(void)goToChicago {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(41.873651,-87.629906, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    0.0f,
                                                    1000.0f);
}

-(void)goToLa {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(34.050175,-118.260048, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    0.0f,
                                                    1800.0f);
}

-(void)goToEdinburgh {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(55.961559,-3.209940, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    77.0f,
                                                    1700.0f);
}

-(void)goToGlasgow {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(55.865242,-4.288697, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    224.0f,
                                                    2320.0f);
}

-(void)goToCambridge {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(52.201092,0.118611, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    319.0f,
                                                    1600.0f);
}

-(void)goToOban {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(56.416794,-5.486794, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    114.0f,
                                                    3000.0f);
}

-(void)goToBarcelona {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(41.382476,2.17804, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    114.0f,
                                                    3000.0f);
}

-(void)goToKyoto {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(34.9977166,135.755402, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                    0.0f,
                                                    1500.0f);
}

-(void)debugPlacesToggleButtonPressedHandler {
	[sf setHidden:!sf.hidden];
	[ldn setHidden:!ldn.hidden];
	[ny setHidden:!ny.hidden];
	[chic setHidden:!chic.hidden];
	[la setHidden:!la.hidden];
	[edin setHidden:!edin.hidden];
	[glasgow setHidden:!glasgow.hidden];
	[sandiego setHidden:!sandiego.hidden];
	[cambridge setHidden:!cambridge.hidden];
	[oban setHidden:!oban.hidden];
	[barcelona setHidden:!barcelona.hidden];
	[kyoto setHidden:!kyoto.hidden];
}


//resource stats
-(void)toggleResourcesDebugItemsHidden:(bool)hidden{
    [resTxtNumResourcesRequested setHidden:hidden];
    [resTxtTotalBytesLoaded setHidden:hidden];
    [resTxtBytesLoadedFromCacheAndWeb setHidden:hidden];
    [resTxtAvgBytesPerSuccessLoad setHidden:hidden];
    [resTxtTotalByRequestOutcome setHidden:hidden];
    [resTxtAvgLoadTimes setHidden:hidden];
    [resTxtAvgBuild setHidden:hidden];
}

-(void)toggleResourceDebug:(UIButton *)btn :(DebuggedResource::ResourceType)res
{
    [currentDebuggedResourceButton setSelected:NO];
    currentDebuggedResourceButton = currentDebuggedResource == res ? NULL : btn;
    currentDebuggedResource = currentDebuggedResource == res ? DebuggedResource::None : res;
    
    if(currentDebuggedResource != DebuggedResource::None)
    {
        [currentDebuggedResourceButton setTitleColor:[UIColor redColor] forState:UIControlStateSelected];
        [currentDebuggedResourceButton setSelected:YES];
        [self toggleResourcesDebugItemsHidden :false];
        [self printResourceStats]; //update immediately on input
    }
    else
    {
        [self toggleResourcesDebugItemsHidden :true];
    }
}

-(void)toggleBuildingResourceDebugInfo {
    [self toggleResourceDebug : resBtnBuildings :DebuggedResource::Buildings];
}

-(void)toggleLandmarkResourceDebugInfo {
}

-(void)toggleLcmResourceDebugInfo {
    [self toggleResourceDebug : resBtnLcm :DebuggedResource::Terrain];
}

-(void)toggleModelResourceDebugInfo {
    [self toggleResourceDebug : resBtnModels :DebuggedResource::Models];
}

-(void)togglePlaceNamesResourceDebugInfo {
    [self toggleResourceDebug : resBtnPlacenames :DebuggedResource::Placenames];
}

-(void)toggleRoadsResourceDebugInfo {
    [self toggleResourceDebug : resBtnRoads :DebuggedResource::Roads];
}

-(void)toggleShadowsResourceDebugInfo {
}

-(void)printResourceStats {
    std::stringstream ss_totalsForAllResources;
    [self getTotalsForAllResources :ss_totalsForAllResources];
    resTxtTotalsForAllRes.text = [NSString stringWithUTF8String:ss_totalsForAllResources.str().c_str()];
    
    //per resource
    std::stringstream ss_totalNumResourcesRequested;
    [self getTotalNumResourcesRequested :ss_totalNumResourcesRequested];
    resTxtNumResourcesRequested.text = [NSString stringWithUTF8String:ss_totalNumResourcesRequested.str().c_str()];
    
    std::stringstream ss_totalBytesLoaded;
    [self getTotalBytesLoaded :ss_totalBytesLoaded];
    resTxtTotalBytesLoaded.text = [NSString stringWithUTF8String:ss_totalBytesLoaded.str().c_str()];
    
    std::stringstream ss_bytesLoadedFromCacheAndWeb;
    [self getBytesFromCacheOrWeb :ss_bytesLoadedFromCacheAndWeb];
    resTxtBytesLoadedFromCacheAndWeb.text = [NSString stringWithUTF8String:ss_bytesLoadedFromCacheAndWeb.str().c_str()];
    
    std::stringstream ss_avgBytesPerSuccessLoad;
    [self getAvgBytesPerSuccessLoad :ss_avgBytesPerSuccessLoad];
    resTxtAvgBytesPerSuccessLoad.text = [NSString stringWithUTF8String:ss_avgBytesPerSuccessLoad.str().c_str()];
    
    std::stringstream ss_totalsByRequestOutcome;
    [self getTotalsByRequestOutcomes :ss_totalsByRequestOutcome];
    resTxtTotalByRequestOutcome.text = [NSString stringWithUTF8String:ss_totalsByRequestOutcome.str().c_str()];
    
    std::stringstream ss_avgLoadTimes;
    [self getAvgLoadTimes :ss_avgLoadTimes];
    resTxtAvgLoadTimes.text = [NSString stringWithUTF8String:ss_avgLoadTimes.str().c_str()];
    
    std::stringstream ss_avgBuild;
    [self getAvgBuildOutupt :ss_avgBuild];
    resTxtAvgBuild.text = [NSString stringWithUTF8String:ss_avgBuild.str().c_str()];
}

-(void)getTotalsForAllResources:(std::stringstream&)ss{
    int totalRequests = 0;
    int totalSuccess = 0;
    int totalFails = 0;
    int totalBytes = 0;
    
    for(std::vector<Eegeo::Streaming::LoggingResourceStream*>::iterator it = streams.begin(); it != streams.end(); ++ it)
    {
        totalRequests += (*it)->TotalNumRequests();
        totalSuccess += (*it)->TotalSuccessRequests();
        totalFails += (*it)->TotalFailedRequests();
        totalBytes += (*it)->TotalBytesSuccessRequests();
    }
    
    totalBytes /= (1024 * 1024);
    
    ss << "Totals :: "
    << totalRequests << " Requests, "
    << totalSuccess << " Successes, "
    << totalFails << " Fails, "
    << totalBytes << " MB Bytes";
}

-(void)getTotalNumResourcesRequested:(std::stringstream&)ss{
    ss << "Total Requests :: ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalNumRequests();
    }
}

-(void)getTotalBytesLoaded:(std::stringstream&)ss{
    ss << "Total Bytes Loaded :: ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalBytesSuccessRequests() / 1024;
    }
    
    ss << " KB";
}

-(void)getBytesFromCacheOrWeb:(std::stringstream&)ss{
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalBytesSuccessRequestsFromWeb() / 1024;
    }
    
    ss << " KB load from web, ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalBytesSuccessRequestsFromCache() / 1024;
    }
    
    ss << " KB load from cache";
}

-(void)getAvgBytesPerSuccessLoad:(std::stringstream&)ss{
    ss << "Avg Bytes Per Successful Load :: ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->AvgBytesPerSuccessRequests() / 1024 << " KB"
        << " for " << streams[currentDebuggedResource]->TotalSuccessRequests() << " requests";
    }
}

-(void)getTotalsByRequestOutcomes:(std::stringstream&)ss{
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalSuccessRequestsFromWeb();
    }
    
    ss << " web loads, ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalSuccessRequestsFromCache();
    }
    
    ss << " cache loads, ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->TotalFailedRequests();
    }
    
    ss << " failed loads";
}

-(void)getAvgLoadTimes:(std::stringstream&)ss{
    ss << "Avg full load times :: ";
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->AvgTimeSuccessWebLoadMs();
    }
    
    ss << " ms web, ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->AvgTimeSuccessCacheLoadMs();
    }
    
    ss << " ms cache, ";
    
    if (currentDebuggedResource != DebuggedResource::None)
    {
        ss << streams[currentDebuggedResource]->AvgTimeFailWebLoadMs();
    }
    
    ss << " ms fail";
}

-(void)getAvgBuildOutupt:(std::stringstream&)ss{
    ss << "Avg Inflate time :: ";
    
    switch(currentDebuggedResource)
    {
        case DebuggedResource::Buildings:
        {
            ss << myApp->World().GetBuildingBuilder().AvgTimeTakenMs()
            << " ms for " << myApp->World().GetBuildingBuilder().NumBuilds() << " builds";
        }break;
        case DebuggedResource::Terrain:
            ss << "LCM: " << myApp->World().GetLcmTerrainBuilder().AvgTimeTakenMs()
            << " ms for " << myApp->World().GetLcmTerrainBuilder().NumBuilds() << " builds";
        {
        }break;
       
        case DebuggedResource::Placenames:
            ss << myApp->World().GetPlaceNamesBuilder().AvgTimeTakenMs()
            << " ms for " << myApp->World().GetPlaceNamesBuilder().NumBuilds() << " builds";
        {
        }break;
        case DebuggedResource::Roads:
            ss << myApp->World().GetRoadBuilder().AvgTimeTakenMs()
            << " ms for " << myApp->World().GetRoadBuilder().NumBuilds() << " builds";
        {
        }break;
        default: break;
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if(App::IsDeviceSmall())
	{
		return (interfaceOrientation == UIInterfaceOrientationPortrait);
	}
	else
	{
		return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
	}
}


- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    piOSLocationService->FailedToGetLocation();
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    CLLocation *currentLocation = newLocation;
    
    if (currentLocation != nil)
    {
        double latDegrees = currentLocation.coordinate.latitude;
        double lonDegrees = currentLocation.coordinate.longitude;
        double altitudeMeters = currentLocation.altitude;
        double accuracyMeters = currentLocation.horizontalAccuracy;
        piOSLocationService->UpdateLocation(latDegrees, lonDegrees, altitudeMeters);
        piOSLocationService->UpdateHorizontalAccuracy(accuracyMeters);
    }
    else
    {
        piOSLocationService->FailedToGetLocation();
    }
}

@end