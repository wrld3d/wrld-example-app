#include <stdio.h>

#include "AppWindow.hpp"
#include "AndroidWebRequestService.hpp"
#include "AndroidTaskQueue.h"
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
#include "EnvironmentFlatteningService.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

#define API_KEY "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE"

void AppWindow::EnqueuePointerEvent(TouchInputEvent& e)
{
	pthread_mutex_lock(&m_inputMutex);
	touchBuffer.push_back(e);
	pthread_mutex_unlock(&m_inputMutex);
}

AppWindow::AppWindow(AndroidNativeState* pState, PersistentAppState* pPersistentState, bool initialStart)
: pState(pState)
, persistentState(pPersistentState)
, pAppOnMap(NULL)
, pInputProcessor(NULL)
, pWorld(NULL)
, pAndroidLocationService(NULL)
, appRunning(false)
, displayAvailable(false)
, worldInitialised(false)
, displayBound(false)
, surfaceChanged(0)
, initialStart(initialStart)
, m_androidInputBoxFactory(pState)
, m_androidKeyboardInputFactory(pState, pInputHandler)
, m_androidAlertBoxFactory(pState)
, m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
, m_terrainHeightRepository()
, m_terrainHeightProvider(&m_terrainHeightRepository)
, m_pEnvironmentFlatteningService(NULL)
, updatedForFirstTime(false)
, context(EGL_NO_CONTEXT)
, resourceBuildShareContext(EGL_NO_CONTEXT)
, pTaskQueue(NULL)
, pHttpCache(NULL)
{

	//Eegeo_TTY("CONSTRUCTING AppWindow");
    pthread_mutex_init(&m_mutex, 0);
    pthread_mutex_init(&m_inputMutex, 0);

    this->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);
}

AppWindow::~AppWindow()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_mutex_destroy(&m_inputMutex);

	TerminateDisplay(true);
	TerminateWorld();
}

void AppWindow::Pause(PersistentAppState* pPersistentState)
{
	pthread_mutex_lock(&m_mutex);
	appRunning = false;
	pthread_mutex_unlock(&m_mutex);

    pthread_join(m_mainNativeThread, 0);

    if(pHttpCache != NULL)
    {
    	pHttpCache->FlushInMemoryCacheRepresentation();
    }

    if(pAndroidLocationService != NULL)
    {
    	pAndroidLocationService->StopListening();
    }

	if(pPersistentState != NULL)
	{
		pPersistentState->lastGlobeCameraDistanceToInterest = this->persistentState.lastGlobeCameraDistanceToInterest;
		pPersistentState->lastGlobeCameraHeadingDegrees = this->persistentState.lastGlobeCameraHeadingDegrees;
		pPersistentState->lastGlobeCameraLatLong = this->persistentState.lastGlobeCameraLatLong;
	}
}

void AppWindow::Resume()
{
	pthread_mutex_lock(&m_mutex);
	appRunning = true;
	displayAvailable = false;
	pthread_mutex_unlock(&m_mutex);

	if(pHttpCache != NULL)
	{
		pHttpCache->ReloadCacheRepresentationFromStorage();
	}

    pthread_create(&m_mainNativeThread, 0, Run, this);
}

void AppWindow::ActivateSurface()
{
	pthread_mutex_lock(&m_mutex);
	surfaceChanged++;
	displayAvailable = true;
	pthread_mutex_unlock(&m_mutex);
}

void* AppWindow::Run(void* self)
{
	Eegeo::Helpers::ThreadHelpers::SetThisThreadAsMainThread();

	AppWindow* pSelf = (AppWindow*)self;
	Eegeo_TTY("STARTING RUN");

    while (1)
    {
    	pthread_mutex_lock(&pSelf->m_mutex);
    	bool running = pSelf->appRunning;
    	bool displayAvailable = pSelf->displayAvailable;
    	bool worldInitialised = pSelf->worldInitialised;
    	bool displayBound = pSelf->displayBound;
    	int surfaceChanged = pSelf->surfaceChanged;
    	pthread_mutex_unlock(&pSelf->m_mutex);

        if(running)
        {
        	if(displayAvailable)
        	{
        		if (displayBound && (surfaceChanged > 0))
        		{
        			pSelf->TerminateDisplay(false);
        			displayBound = false;
        		}

        		if(!displayBound)
				{
					if(!pSelf->InitDisplay())
					{
						continue;
					}
				}

        		if(!worldInitialised)
        		{
        			pSelf->InitWorld();
        		}

        		if(!pSelf->updatedForFirstTime)
        		{
        			Eegeo_TTY("First call to EegeoWorld::Update()\n");
        			pSelf->updatedForFirstTime = true;
        		}
            	pSelf->UpdateWorld();
        	}
        }
        else
        {
        	if(displayAvailable)
        	{
        		Eegeo::Camera::GlobeCamera::GlobeCameraController& getCameraController = pSelf->GetAppOnMap().GetCameraController();

        	    const Eegeo::Space::EcefTangentBasis& cameraInterest = getCameraController.GetInterestBasis();
        	    const float cameraHeadingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterest.GetPointEcef(), cameraInterest.GetForward());

        	    pSelf->persistentState.lastGlobeCameraDistanceToInterest = getCameraController.GetDistanceToInterest();
        	    pSelf->persistentState.lastGlobeCameraHeadingDegrees = Eegeo::Math::Rad2Deg(cameraHeadingRadians);
        	    pSelf->persistentState.lastGlobeCameraLatLong = Eegeo::Space::LatLongAltitude::FromECEF(cameraInterest.GetPointEcef());

        	    pSelf->TerminateDisplay(false);
        		pSelf->displayAvailable = false;
        		pSelf->displayBound = false;
        	}

            pthread_exit(0);
        	break;
        }
    }

    return NULL;
}

void AppWindow::UpdateWorld()
{
	if(pWorld!= NULL)
	{
		//get latest input buffer
		std::vector<TouchInputEvent> inputs;
		pthread_mutex_lock(&m_inputMutex);
		inputs = touchBuffer;
		touchBuffer.clear();
		pthread_mutex_unlock(&m_inputMutex);

		//process input events
		size_t events = inputs.size();
		for(size_t i = 0; i < events; ++ i)
		{
			this->pInputProcessor->HandleInput(inputs[i]);
		}

		//update and render world
		//Eegeo_TTY("UPDATING WORLD");
	    Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		float fps = 1.0f/30.0f;
		pAndroidWebRequestService->Update();
		pAppOnMap->Update(fps);
		pAppOnMap->Draw(fps);

		Eegeo_GL(glFinish());
		Eegeo_GL(eglSwapBuffers(display, surface));
	}
}

// based on nVidia example app for Tegra
bool DefaultEGLChooser(EGLDisplay disp, u32 requestedSurfaceType, EGLConfig& bestConfig)
{
	EGLint count = 0;
	if (!eglGetConfigs(disp, NULL, 0, &count))
	{
		Eegeo_TTY("defaultEGLChooser cannot query count of all configs");
		return false;
	}

	Eegeo_TTY("Config count = %d", count);

	EGLConfig* configs = new EGLConfig[count];
	if (!eglGetConfigs(disp, configs, count, &count))
	{
		Eegeo_TTY("defaultEGLChooser cannot query all configs");
		return false;
	}

	int bestMatch = 1<<30;
	int bestIndex = -1;

	int i;
	for (i = 0; i < count; i++)
	{
		int match = 0;
		EGLint surfaceType = 0;
		EGLint blueBits = 0;
		EGLint greenBits = 0;
		EGLint redBits = 0;
		EGLint alphaBits = 0;
		EGLint depthBits = 0;
		EGLint stencilBits = 0;
		EGLint renderableFlags = 0;

		eglGetConfigAttrib(disp, configs[i], EGL_SURFACE_TYPE, &surfaceType);
		eglGetConfigAttrib(disp, configs[i], EGL_BLUE_SIZE, &blueBits);
		eglGetConfigAttrib(disp, configs[i], EGL_GREEN_SIZE, &greenBits);
		eglGetConfigAttrib(disp, configs[i], EGL_RED_SIZE, &redBits);
		eglGetConfigAttrib(disp, configs[i], EGL_ALPHA_SIZE, &alphaBits);
		eglGetConfigAttrib(disp, configs[i], EGL_DEPTH_SIZE, &depthBits);
		eglGetConfigAttrib(disp, configs[i], EGL_STENCIL_SIZE, &stencilBits);
		eglGetConfigAttrib(disp, configs[i], EGL_RENDERABLE_TYPE, &renderableFlags);


		if ((surfaceType & requestedSurfaceType) == 0)
			continue;
		if ((renderableFlags & EGL_OPENGL_ES2_BIT) == 0)
			continue;

		if (depthBits < 16)
			continue;
		if ((redBits < 5) || (greenBits < 6) || (blueBits < 5))
			continue;
		if (stencilBits < 8)
			continue;

		int penalty = depthBits - 16;
		match += penalty * penalty;
		penalty = redBits - 5;
		match += penalty * penalty;
		penalty = greenBits - 6;
		match += penalty * penalty;
		penalty = blueBits - 5;
		match += penalty * penalty;
		penalty = alphaBits;
		match += penalty * penalty;
		penalty = stencilBits - 8;
		match += penalty * penalty;

		if ((match < bestMatch) || (bestIndex == -1))
		{
			bestMatch = match;
			bestIndex = i;
			Eegeo_TTY("New best Config[%d]: R%dG%dB%dA%d D%dS%d Type=%04x Render=%04x",
				i, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, surfaceType, renderableFlags);
		}
	}

	if (bestIndex < 0)
	{
		delete[] configs;
		return false;
	}

	bestConfig = configs[bestIndex];
	delete[] configs;

	return true;
}

bool AppWindow::InitDisplay()
{
    EGLint w, h, dummy, format;
    EGLConfig config;
    EGLSurface surface;

    if (!DefaultEGLChooser(display, EGL_WINDOW_BIT, config))
    {
    	Eegeo_ERROR("unabled to find a good display type");
    	return false;
    }

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(pState->window, 0, 0, format);

    static const EGLint contextAttribs[] = {
              EGL_CONTEXT_CLIENT_VERSION,        2,
              EGL_NONE
           };

    surface = eglCreateWindowSurface(display, config, pState->window, NULL);

    if(context == EGL_NO_CONTEXT) {
    	context = eglCreateContext(display, config, NULL, contextAttribs);
    }

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
    	Eegeo_ERROR("Unable to eglMakeCurrent");
        return false;
    }

    //Eegeo_TTY("printing extensions\n");
    //char * extensionsString =  (char *) glGetString(GL_EXTENSIONS);
    //Eegeo_TTY("%s\n",extensionsString);

    Eegeo_GL(eglQuerySurface(display, surface, EGL_WIDTH, &w));
    Eegeo_GL(eglQuerySurface(display, surface, EGL_HEIGHT, &h));

    this->surface = surface;

#ifdef EEGEO_DROID_EMULATOR
    this->shareSurface = EGL_NO_SURFACE;
    this->resourceBuildShareContext = EGL_NO_CONTEXT;
#else

    if(resourceBuildShareContext == EGL_NO_CONTEXT) {
    	resourceBuildShareContext = eglCreateContext(display, config, context, contextAttribs);
    }

    EGLint pbufferAttribs[] =
        {
            EGL_WIDTH, 1,
            EGL_HEIGHT, 1,
            EGL_TEXTURE_TARGET, EGL_NO_TEXTURE,
            EGL_TEXTURE_FORMAT, EGL_NO_TEXTURE,
            EGL_NONE
        };
    EGLConfig sharedSurfaceConfig;
    if (!DefaultEGLChooser(display, EGL_PBUFFER_BIT, sharedSurfaceConfig))
    {
    	Eegeo_ERROR("unabled to find a good pbuffer surface type");
    }

    this->shareSurface = eglCreatePbufferSurface(display, sharedSurfaceConfig, pbufferAttribs);

    if(pTaskQueue != NULL) {
    	pTaskQueue->UpdateSurface(shareSurface);
    }

#endif
    this->width = w;
    this->height = h;

	glViewport(0, 0, width, height);
	pInputHandler.SetViewportOffset(0, 0);

    // Initialize GL state.
    Eegeo_GL(glClearDepthf(1.0f));
	Eegeo_GL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	// Set up default Depth test.
	Eegeo_GL(glEnable(GL_DEPTH_TEST));
	Eegeo_GL(glDepthMask(GL_TRUE));
	Eegeo_GL(glDepthFunc(GL_LEQUAL));

	// Set up default culling.
	Eegeo_GL(glEnable(GL_CULL_FACE));
	Eegeo_GL(glFrontFace(GL_CW));
	Eegeo_GL(glCullFace(GL_BACK));

	// Turn off the stencil test.
	Eegeo_GL(glDisable(GL_STENCIL_TEST));
	Eegeo_GL(glStencilFunc(GL_NEVER, 0, 0xFFFFFFFF));
	Eegeo_GL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));

	// Set the default blend mode and colour mask.
	Eegeo_GL(glDisable(GL_BLEND));
	Eegeo_GL(glColorMask(true, true, true, true));

	Eegeo_GL(glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	eglSwapInterval(display, 1);

	pthread_mutex_lock(&m_mutex);
	displayBound = true;
	surfaceChanged--;
	pthread_mutex_unlock(&m_mutex);

	return true;
}


void AppWindow::TerminateWorld()
{
	pTaskQueue->StopWorkQueue();

	delete pAppOnMap;
	pHttpCache->FlushInMemoryCacheRepresentation();


    delete m_pInterestPointProvider;

    delete pWorld;
    pWorld = NULL;

    delete pAndroidUrlEncoder;
    delete pAndroidLocationService;
    delete pRenderContext;
    delete pLighting;
    delete pFileIO;
    delete pHttpCache;
    delete pTextureLoader;
    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();
    pBlitter->Shutdown();
    delete pBlitter;
    delete pAndroidWebRequestService;
    delete pAndroidWebLoadRequestFactory;
    delete m_pEnvironmentFlatteningService;

    delete pTaskQueue;
}

void AppWindow::TerminateDisplay(bool teardownEGL)
{
    if (this->display != EGL_NO_DISPLAY)
    {
    	Eegeo_GL(eglMakeCurrent(this->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));

    	if (this->surface != EGL_NO_SURFACE)
		{
			Eegeo_GL(eglDestroySurface(this->display, this->surface));
		}

    	if (this->shareSurface != EGL_NO_SURFACE)
		{
    		Eegeo_GL(eglDestroySurface(this->display, this->shareSurface));
		}

    	if(teardownEGL)
    	{
			if (this->context != EGL_NO_CONTEXT)
			{
				Eegeo_GL(eglDestroyContext(this->display, this->context));
			}

			if(this->resourceBuildShareContext != EGL_NO_CONTEXT)
			{
				Eegeo_GL(eglDestroyContext(this->display, this->resourceBuildShareContext));
			}

			Eegeo_GL(eglTerminate(this->display));

			this->display = EGL_NO_DISPLAY;
		    this->context = EGL_NO_CONTEXT;
		    this->resourceBuildShareContext = EGL_NO_CONTEXT;
    	}
    }

    this->surface = EGL_NO_SURFACE;
    this->shareSurface = EGL_NO_SURFACE;
}

void AppWindow::InitWorld()
{
	pAndroidUrlEncoder = new AndroidUrlEncoder(pState);
	pAndroidLocationService = new AndroidLocationService(pState);

	pRenderContext = new Eegeo::Rendering::RenderContext();
	pRenderContext->SetScreenDimensions(width, height, 1.0f, pState->deviceDpi);

	pLighting = new Eegeo::Lighting::GlobalLighting();
	pFogging = new Eegeo::Lighting::GlobalFogging();
	pShadowing = new Eegeo::Lighting::GlobalShadowing();
	m_pEnvironmentFlatteningService = new Eegeo::Rendering::EnvironmentFlatteningService();

	std::set<std::string> customApplicationAssetDirectories;
	customApplicationAssetDirectories.insert("MyAppDataDirectory");
	customApplicationAssetDirectories.insert("MyAppDataDirectory/MySubDirectory");
	pFileIO = new AndroidFileIO(pState, customApplicationAssetDirectories);

	pHttpCache = new AndroidHttpCache(pFileIO, "http://d2xvsc8j92rfya.cloudfront.net/");
	pTextureLoader = new AndroidTextureFileLoader(pFileIO, pRenderContext->GetGLState());

	Eegeo::EffectHandler::Initialise();
	pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, *pRenderContext);
	pBlitter->Initialise();

	pTaskQueue = new AndroidTaskQueue(10, resourceBuildShareContext, shareSurface, display);

	const int webLoadPoolSize = 10;
	const int cacheLoadPoolSize = 40;
	const int cacheStorePoolSize = 20;
	pAndroidWebRequestService = new AndroidWebRequestService(*pFileIO, pHttpCache, pTaskQueue, webLoadPoolSize, cacheLoadPoolSize, cacheStorePoolSize);

	pAndroidWebLoadRequestFactory = new AndroidWebLoadRequestFactory(pAndroidWebRequestService, pHttpCache);

	m_pInterestPointProvider = new Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider();

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
	std::string deviceModel = std::string(pState->deviceModel, strlen(pState->deviceModel));
	Eegeo::Config::PlatformConfig config = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	pWorld = new Eegeo::EegeoWorld(API_KEY,
            pHttpCache,
            pFileIO,
            pTextureLoader,
            pAndroidWebLoadRequestFactory,
            pTaskQueue,
            *pRenderContext,
            pLighting,
            pFogging,
            pShadowing,
            pAndroidLocationService,
            pBlitter,
            pAndroidUrlEncoder,
            *m_pInterestPointProvider,
            m_androidNativeUIFactories,
            &m_terrainHeightRepository,
            &m_terrainHeightProvider,
            m_pEnvironmentFlatteningService,
            environmentCharacterSet,
            config,
            new Eegeo::Search::Service::SearchServiceCredentials("", ""),
            "",
            "Default-Landscape@2x~ipad.png",
            "http://cdn1.eegeo.com/coverage-trees/v207/manifest.txt.gz",
            "http://cdn1.eegeo.com/mobile-themes-new/v99/manifest.txt.gz",
            NULL,
            (initialStart) ? Eegeo::Rendering::LoadingScreenLayout::FullScreen : Eegeo::Rendering::LoadingScreenLayout::Centred
            );

	pAppOnMap = new MyApp(&pInputHandler, *pState, *m_pInterestPointProvider);
	pInputProcessor = new Eegeo::Android::Input::AndroidInputProcessor(&pInputHandler, pRenderContext->GetScreenWidth(), pRenderContext->GetScreenHeight());

	pAppOnMap->Start(pWorld);

	if (persistentState.valid)
	{
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(persistentState.lastGlobeCameraLatLong.ToECEF(), persistentState.lastGlobeCameraHeadingDegrees, cameraInterestBasis);
		pAppOnMap->GetCameraController().SetView(cameraInterestBasis, persistentState.lastGlobeCameraDistanceToInterest);
	}

    pthread_mutex_lock(&m_mutex);
    worldInitialised = true;
    pthread_mutex_unlock(&m_mutex);
}
