#include "ViewController.h"
#include "App.h"
#include "EnvironmentFlatteningService.h"
#include "IAppOnMap.h"
#include "EegeoWorld.h"
#include "GLState.h"
#include "RenderContext.h"
#include "iOSTaskQueue.h"
#include "iOSFileIO.h"
#include "iOSTextureFileLoader.h"
#include "iOSWebLoadRequestFactory.h"
#include "SearchServiceCredentials.h"
#include "GlobeCameraInterestPointProvider.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "iOSPlatformConfigBuilder.h"
#include "RouteMatchingExampleFactory.h"
#include "RouteSimulationExampleFactory.h"

const std::string ApiKey = "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE";

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

@implementation ViewController

- (void)dealloc {
    [super dealloc];
    delete m_pEnvironmentFlatteningService;
    Eegeo_DELETE m_piOSRouteMatchingExampleViewFactory;
    Eegeo_DELETE m_piOSExampleControllerView;
    Eegeo_DELETE m_pExampleController;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = self;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    locationManager.headingFilter = kCLHeadingFilterNone;
    
    [locationManager startUpdatingLocation];
    [locationManager startUpdatingHeading];
    
    previousTimestamp = CFAbsoluteTimeGetCurrent();
    
    pixelScale = 1.0f;
    m_pInterestPointProvider = NULL;
    piOSLocationService = NULL;
    m_terrainHeightProvider = Eegeo_NEW(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider)(&m_terrainHeightRepository);
    m_pEnvironmentFlatteningService = NULL;
    m_pExampleController = NULL;
    m_piOSRouteMatchingExampleViewFactory = NULL;
    
    nativeUIFactories = Eegeo_NEW(Eegeo::UI::NativeUIFactories)(alertBoxFactory, inputBoxFactory, keyboardInputFactory);
    
    webRequestService = NULL;
    
    [self initInputs];
    [self initGraphics];
    [self initWorld];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    m_pExampleApp->Draw(1.0f/60.0f);
    
    const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
    Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));
}

- (void)update
{
    CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
    CFTimeInterval frameDuration = timeNow - previousTimestamp;
    
    m_pExampleApp->Update(frameDuration);
        
    self.preferredFramesPerSecond = 60.0f;
    
    previousTimestamp = timeNow;
    
    webRequestService->Update();
}

- (void) initGraphics
{
	App::Initialise();
    
    GLKViewDrawableMultisample multiSample;
    
    if (App::IsDeviceSmall())
    {
        // AA on for high-performance small devices (phones >= GAME_DEVICE_IPHONE4S, ipods >= GAME_DEVICE_IPOD5)
        multiSample = App::IsDeviceMultiCore() ? GLKViewDrawableMultisample4X : GLKViewDrawableMultisampleNone;
    }
    else
    {
        // AA on for GAME_DEVICE_IPAD2 / GAME_DEVICE_IPADMINI_1GEN
        multiSample = (App::IsDeviceMultiCore() && !App::HasRetinaDisplay()) ? GLKViewDrawableMultisample4X : GLKViewDrawableMultisampleNone;
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
    
    float width 		= view.bounds.size.width * pixelScale;
    float height 		= view.bounds.size.height * pixelScale;
    
	bool boPortrait = App::IsDeviceSmall();
	
    if (!boPortrait) {
        float temp = width;
        width = height;
        height = temp;
    }
    
    m_renderContext = new Eegeo::Rendering::RenderContext();
    m_renderContext->SetScreenDimensions(width, height, pixelScale, App::GetDeviceDpi()*pixelScale);
}

- (void) initWorld
{
    Eegeo::EffectHandler::Initialise();

    piOSLocationService = new iOSLocationService;
    
    m_pInterestPointProvider = Eegeo_NEW(Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider());

    m_pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, *m_renderContext);
    m_pBlitter->Initialise();
    
    Eegeo::Lighting::GlobalLighting* pLighting = new Eegeo::Lighting::GlobalLighting();
    Eegeo::Lighting::GlobalFogging* pFogging = new Eegeo::Lighting::GlobalFogging();
    Eegeo::Lighting::GlobalShadowing* pShadowing = new Eegeo::Lighting::GlobalShadowing();
    m_pEnvironmentFlatteningService = new Eegeo::Rendering::EnvironmentFlatteningService();
    
    iOSFileIO* p_iOSFileIO = new iOSFileIO();
    Eegeo::Helpers::IFileIO* pFileIO = p_iOSFileIO;
    Eegeo::Helpers::ITextureFileLoader* pTextureFileLoader = new iOSTextureFileLoader(p_iOSFileIO, m_renderContext->GetGLState());
    iOSHttpCache* p_iOSHttpCache = new iOSHttpCache(*p_iOSFileIO);
    Eegeo::Helpers::IHttpCache* pHttpCache = p_iOSHttpCache;
    
    webRequestService = new Eegeo::Web::iOSWebRequestService();
    
    Eegeo::Web::IWebLoadRequestFactory* pPayloadRequestFactory = new Eegeo::Web::iOSWebLoadRequestFactory(*p_iOSHttpCache, *webRequestService);
    Eegeo::Helpers::ITaskQueue* pTaskQueue = new iOSTaskQueue(10);
    
    const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
    Eegeo::Config::PlatformConfig config = Eegeo::iOS::iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore()).Build();
    
    Eegeo::EegeoWorld* pWorld = new Eegeo::EegeoWorld(ApiKey,
                                                      pHttpCache,
                                                      pFileIO,
                                                      pTextureFileLoader,
                                                      pPayloadRequestFactory,
                                                      pTaskQueue,
                                                      *m_renderContext,
                                                      pLighting,
                                                      pFogging,
                                                      pShadowing,
                                                      piOSLocationService,
                                                      m_pBlitter,
                                                      &iOSUrlEncoder,
                                                      *m_pInterestPointProvider,
                                                      *nativeUIFactories,
                                                      &m_terrainHeightRepository,
                                                      m_terrainHeightProvider,
                                                      m_pEnvironmentFlatteningService,
                                                      environmentCharacterSet,
                                                      config,
                                                      pCredentials,
                                                      "",
                                                      "Default-Landscape@2x~ipad.png"
                                                      );
    
    m_piOSExampleControllerView = Eegeo_NEW(Examples::iOSExampleControllerView)([self view]);
    m_pExampleController = Eegeo_NEW(Examples::ExampleController)(*pWorld, *m_piOSExampleControllerView);
    
    m_pExampleApp = new ExampleApp(pWorld, *m_pInterestPointProvider, *m_pExampleController);
    
    //register examples with platform-specific view factories (i.e., pointer to [self view])
    
    m_piOSRouteMatchingExampleViewFactory = Eegeo_NEW(Examples::iOSRouteMatchingExampleViewFactory)([self view]);
    m_pExampleController->RegisterExample(Eegeo_NEW(Examples::RouteMatchingExampleFactory)(*pWorld, *m_piOSRouteMatchingExampleViewFactory));
    
    m_piOSRouteSimulationExampleViewFactory = Eegeo_NEW(Examples::iOSRouteSimulationExampleViewFactory)([self view]);
    m_pExampleController->RegisterExample(Eegeo_NEW(Examples::RouteSimulationExampleFactory)(*pWorld, m_pExampleApp->GetCameraController(), *m_piOSRouteSimulationExampleViewFactory));
    
    // start examples
    m_pExampleController->ActivatePrevious();
    
    m_renderContext->GetGLState().InvalidateAll();
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
}

-(void)gestureRotation_Callback:(UIRotationGestureRecognizer*)recognizer
{
	AppInterface::RotateData data;
	
	data.rotation	= recognizer.rotation;
	data.numTouches	= recognizer.numberOfTouches;
    data.velocity = recognizer.velocity;
	
    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_pExampleApp->Event_TouchRotate_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        m_pExampleApp->Event_TouchRotate (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        m_pExampleApp->Event_TouchRotate_End (data);
    }
}

-(void)gesturePinch_Callback:(UIPinchGestureRecognizer*)recognizer
{
    float dist;
    static bool reset = true;
    
    if (recognizer.numberOfTouches == 2)
    {
        CGPoint point0 = [recognizer locationOfTouch:0 inView:self.view];
        CGPoint point1 = [recognizer locationOfTouch:1 inView:self.view];
        
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
        m_pExampleApp->Event_TouchPinch_Start(data);
        
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        float delta = (_previousDist-dist);
        float majorScreenDimension = fmaxf(m_renderContext->GetScreenHeight(), m_renderContext->GetScreenWidth());
		data.scale = delta/majorScreenDimension;
        m_pExampleApp->Event_TouchPinch (data);
        _previousDist = dist;
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
		data.scale	= recognizer.scale;
        m_pExampleApp->Event_TouchPinch_End (data);
    }
    
    _previousDist = dist;
}

-(Eegeo::v2)getGestureTouchExtents:(UIGestureRecognizer*)recognizer
{
    Eegeo::v2 touchExtents = Eegeo::v2::Zero();
    if (recognizer.numberOfTouches > 1)
    {
        CGPoint extentsMax = [recognizer locationOfTouch:0 inView:self.view];
        CGPoint extentsMin = extentsMax;
        for (int i = 1; i < recognizer.numberOfTouches; ++i)
        {
            CGPoint point = [recognizer locationOfTouch:i inView:self.view];
            extentsMax.x = std::max(extentsMax.x, point.x);
            extentsMax.y = std::max(extentsMax.y, point.y);
            extentsMin.x = std::min(extentsMin.x, point.x);
            extentsMin.y = std::min(extentsMin.y, point.y);
        }
        
        CGPoint extents = extentsMax;
        extents.x -= extentsMin.x;
        extents.y -= extentsMin.y;
        touchExtents = *(Eegeo::v2*)&extents;
    }
    return touchExtents;
}

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
    data.majorScreenDimension = majorScreenDimension;
    data.numTouches = recognizer.numberOfTouches;
    data.touchExtents = [self getGestureTouchExtents :recognizer];
	
    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_pExampleApp->Event_TouchPan_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        m_pExampleApp->Event_TouchPan (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        m_pExampleApp->Event_TouchPan_End (data);
    }
}

-(void)gestureTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:self.view];
        
		position.x *= pixelScale;
		position.y *= pixelScale;
		
		AppInterface::TapData data;
		
		data.point	= *(Eegeo::v2*)&position;
        
        m_pExampleApp->Event_TouchTap (data);
        
    }
}

-(void)gestureDoubleTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:self.view];
		
		position.x *= pixelScale;
		position.y *= pixelScale;
        
		AppInterface::TapData data;
		
		data.point	= *(Eegeo::v2*)&position;
        
        m_pExampleApp->Event_TouchDoubleTap (data);
        
    }
}

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
        
        m_pExampleApp->Event_TouchDown (data);
    }
}

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
        
        m_pExampleApp->Event_TouchMove (data);
    }
}

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
        
        m_pExampleApp->Event_TouchUp (data);
    }
}


- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

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
    piOSLocationService->FailedToGetHeading();
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

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    if (newHeading.headingAccuracy >= 0)
    {
        piOSLocationService->UpdateHeading(newHeading.trueHeading);
    }
    else
    {
        piOSLocationService->FailedToGetHeading();
    }
}

@end