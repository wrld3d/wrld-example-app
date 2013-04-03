#import "ASIHTTPRequest.h"
#import "ViewController.h"
#import "ResourceCache.h"

#include "Game.h"

#include "GraphicsCore.h"

#include <sys/types.h>
#include <sys/sysctl.h>

#import "External/Reachability/Reachability.h"
#include "DebugValues.h"
#include "CameraModel.h"
#include "PrecachingService.h"
#include "NewGlobeCamera.h"
#include "MeshPool.h"
#include "StreamingController.h"
#include "EegeoEnvironmentRendering.h"
#include "MaterialRepository.h"
#include "StencilShadowMaterial.h"
#include "DefaultMaterialFactory.h"

#include "AppOnMap.h"
#include "IOSHelper.h"
#include <sstream>

@interface ViewController()
{
    
}


@property (strong, nonatomic) EAGLContext *context;


@end


@implementation ViewController

CFTimeInterval previousTimestamp = CFAbsoluteTimeGetCurrent();
CFTimeInterval smoothedFrameDuration = 0.1;
CFTimeInterval debugStatsUpdateExpiry = 0;

@synthesize fps;
@synthesize smoothedFrameTime;
@synthesize mem;
@synthesize terrains;
@synthesize buildings;
@synthesize models;
@synthesize camera;
@synthesize payloads;
@synthesize renderData;

@synthesize debug;
@synthesize clearCache;
@synthesize precacheVolume;
@synthesize precacheVolumeProgress;
@synthesize toggleMidokiModels;
@synthesize streamingEnabled;

//debug places
@synthesize places;
@synthesize sf;
@synthesize ldn;
@synthesize ny;
@synthesize chic;
@synthesize la;
@synthesize edin;
@synthesize dun;

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)dealloc {
    [super dealloc];
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

-(void)debugControlsToggleButtonPressedHandler {
    
	[fps setHidden:!fps.hidden];
    [smoothedFrameTime setHidden:!smoothedFrameTime.hidden];
	[mem setHidden:!mem.hidden];
	[terrains setHidden:!terrains.hidden];
	[buildings setHidden:!buildings.hidden];
	[renderData setHidden:!renderData.hidden];
	[models setHidden:!models.hidden];
	[camera setHidden:!camera.hidden];
	[clearCache setHidden:!clearCache.hidden];
	[wireframeBuildings setHidden:!wireframeBuildings.hidden];
	[streamingEnabled setHidden:!streamingEnabled.hidden];
	[toggleMidokiModels setHidden:!toggleMidokiModels.hidden];
    [payloads setHidden:!payloads.hidden];
    [precacheVolume setHidden:!precacheVolume.hidden];
    [precacheVolumeProgress setHidden:!precacheVolumeProgress.hidden];
}

-(void)beginPrecacheVolume {
    Eegeo::Streaming::IStreamingVolume& volume = myApp->World().GetStreamingVolume();
    myApp->World().GetPrecachingService().Precache(&volume);
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
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(51.508315,-0.126446, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)goToNy {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(40.774562,-73.965038, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)goToChicago {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(41.873651,-87.629906, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)goToLa {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(34.051806,-118.2433, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)goToEdinburgh {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(55.948611,-3.200308, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)goToDundee {
    myApp->pGlobeCamera->SetInterestHeadingDistance(Eegeo::Space::LatLongAltitude(56.459948,-2.978123, 0, Eegeo::Space::LatLongUnits::Degrees),
                                                       0.0f,
                                                       1000.0f);
}

-(void)debugPlacesToggleButtonPressedHandler {
	[sf setHidden:!sf.hidden];
	[ldn setHidden:!ldn.hidden];
	[ny setHidden:!ny.hidden];
	[chic setHidden:!chic.hidden];
	[la setHidden:!la.hidden];
	[edin setHidden:!edin.hidden];
	[dun setHidden:!dun.hidden];
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)viewDidLoad
{
    [super viewDidLoad];

    Eegeo::RenderCamera* pMdkCamera = new Eegeo::RenderCamera();
    Eegeo::Camera::CameraModel*  pCameraModel = new Eegeo::Camera::CameraModel(pMdkCamera);
    Eegeo::Camera::NewGlobeCamera* gc = new Eegeo::Camera::NewGlobeCamera(pCameraModel, pMdkCamera);
    Eegeo::Rendering::IMaterialFactory* materialFactory = new Eegeo::Rendering::DefaultMaterialFactory();
    
    // Setup the Game
    myApp = new ::MyApp(gc);
    
    pApp = new Game(self,
                    UIInterfaceOrientationIsLandscape(self.interfaceOrientation) == false,
                    myApp,
                    pMdkCamera,
                    pCameraModel,
                    gc,
                    materialFactory,
                    false);
    
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
    
    [self debugControlsToggleButtonPressedHandler];
    
    //debug places
    [places addTarget:self action:@selector(debugPlacesToggleButtonPressedHandler) forControlEvents:UIControlEventTouchUpInside];
    [sf addTarget:self action:@selector(goToSf) forControlEvents:UIControlEventTouchUpInside];
    [ldn addTarget:self action:@selector(goToLdn) forControlEvents:UIControlEventTouchUpInside];
    [ny addTarget:self action:@selector(goToNy) forControlEvents:UIControlEventTouchUpInside];
    [chic addTarget:self action:@selector(goToChicago) forControlEvents:UIControlEventTouchUpInside];
    [la addTarget:self action:@selector(goToLa) forControlEvents:UIControlEventTouchUpInside];
    [edin addTarget:self action:@selector(goToEdinburgh) forControlEvents:UIControlEventTouchUpInside];
    [dun addTarget:self action:@selector(goToDundee) forControlEvents:UIControlEventTouchUpInside];
    [precacheVolume addTarget:self action:@selector(beginPrecacheVolume) forControlEvents:UIControlEventTouchUpInside];
    
    [self debugPlacesToggleButtonPressedHandler];
}

// ---------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------
- (void)update
{
    [super update];
    
    CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
    CFTimeInterval frameDuration = timeNow - previousTimestamp;
    smoothedFrameDuration += (frameDuration - smoothedFrameDuration)*0.03;
    previousTimestamp = timeNow;
    
    if(precaching)
    {
        const Eegeo::Web::PrecachingService& precachingService = myApp->World().GetPrecachingService();
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
    
    const float debugUpdateIntervalSeconds = 1.0f;
    debugStatsUpdateExpiry = timeNow + debugUpdateIntervalSeconds;
    
    std::stringstream ss_fps;
    ss_fps << "FPS:: " << (1.0/smoothedFrameDuration);
    fps.text = [NSString stringWithUTF8String:ss_fps.str().c_str()];
    
    std::stringstream ss_smoothedFrameTime;
    ss_smoothedFrameTime << "FT: " << (smoothedFrameDuration*1000.0) << "ms";
    smoothedFrameTime.text = [NSString stringWithUTF8String:ss_smoothedFrameTime.str().c_str()];
    
    std::stringstream ss_mem;
    ss_mem << "Mem:: " << IOSHelper::GetTaskTotalMemoryUsageInBytes();
    mem.text = [NSString stringWithUTF8String:ss_mem.str().c_str()];
    
    std::stringstream ss_terrains;
    Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& terrainPool = myApp->World().GetTerrainMeshPool();
    ss_terrains << "Terrains:: " << terrainPool.GetCount() << "/" <<  terrainPool.GetCapacity();
    terrains.text = [NSString stringWithUTF8String:ss_terrains.str().c_str()];
    
    std::stringstream ss_buildings;
    Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool = myApp->World().GetBuildingMeshPool();
    ss_buildings << "Buildings:: " << buildingPool.GetCount() << "/" <<  buildingPool.GetCapacity();
    buildings.text = [NSString stringWithUTF8String:ss_buildings.str().c_str()];
    
    std::stringstream ss_models;
    Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& modelPool = myApp->World().GetModelMeshPool();
    ss_models << "Models:: " << modelPool.GetCount() << "/" <<  modelPool.GetCapacity();
    models.text = [NSString stringWithUTF8String:ss_models.str().c_str()];
    
    std::stringstream ss_payloads;
    ss_payloads << "Payloads:: " << Eegeo::Debug::DebugValues::numPayloadsToLoad << " waiting to load." << Eegeo::Debug::DebugValues::numPayloadsToBuild << " waiting to build.";
    payloads.text = [NSString stringWithUTF8String:ss_payloads.str().c_str()];
    
    float rot = myApp->pGlobeCamera->CurrentRotationRadians();
    rot = fmodf(Eegeo::Math::Rad2Deg(rot), 360.0f);
    if(rot < 0.0f) rot = 360.0f + rot;
    
    Eegeo::Space::LatLongAltitude loc = Eegeo::Space::LatLongAltitude::FromECEF(myApp->World().GetCameraModel().GetWorldPosition());
    char cameraParams[200];
    sprintf (
             cameraParams,
             "Lat=%0.4f Long=%0.4f, Alt=%0.4f, Rot=%0.4f",
             loc.GetLatitudeInDegrees(),
             loc.GetLongitudeInDegrees(),
             loc.GetAltitude(),
             rot
             );
    camera.text = [NSString stringWithUTF8String:cameraParams];
    
    std::stringstream ss_renderdata;
    ss_renderdata << "Polys :: " << Eegeo::Debug::DebugValues::totalPolysRendered << ", Shadow Polys ::" << Eegeo::Debug::DebugValues::shadowPolysRendered << ", Batches :: " << Eegeo::Debug::DebugValues::totalDrawCalls << ", ShadowDraw :: " << Eegeo::Debug::DebugValues::totalShadowDrawCalls;
    renderData.text = [NSString stringWithUTF8String:ss_renderdata.str().c_str()];
}


@end


