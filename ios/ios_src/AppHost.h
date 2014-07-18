// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPHOST_H_
#define APPHOST_H_

#include "Types.h"
#include "Graphics.h"
#include "iOSFileIO.h"
#include "iOSHttpCache.h"
#include "iOSTextureFileLoader.h"
#include "iOSWebLoadRequestFactory.h"
#include "iOSLocationService.h"
#include "iOSUrlEncoder.h"
#include "GlobeCameraInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightRepository.h"
#include "GlobalShadowing.h"
#include "TouchEventWrapper.h"
#include "Blitter.h"
#include "AppInputDelegate.h"
#include "AppLocationDelegate.h"
#include "IGlTaskContextFactory.h"
#include <vector>

//example app includes
#include "ExampleApp.h"
#include "ExampleController.h"
#include "iOSExampleControllerView.h"
#include "iOSRouteMatchingExampleViewFactory.h"
#include "iOSRouteSimulationExampleViewFactory.h"

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : protected Eegeo::NonCopyable
{
public:
	AppHost(
	    const std::string& apiKey,
        ViewController& viewController,
	    float displayWidth,
	    float displayHeight,
        float deviceDpi,
        float pixelScale
	);
	~AppHost();

	void Update(float dt);
	void Draw(float dt);

	void OnPause();
	void OnResume();
    
	void SetViewportOffset(float x, float y);

private:
    ViewController& m_viewController;
	Eegeo::Rendering::EnvironmentFlatteningService* m_pEnvironmentFlatteningService;
	Eegeo::Web::iOSWebLoadRequestFactory* m_piOSWebLoadRequestFactory;
	Eegeo::Web::iOSWebRequestService* m_piOSWebRequestService;
	Eegeo::Blitter* m_pBlitter;
	Eegeo::iOS::iOSTextureFileLoader* m_pTextureLoader;
	iOSHttpCache* m_pHttpCache;
	Eegeo::iOS::iOSFileIO* m_pFileIO;
	Eegeo::Lighting::GlobalLighting* m_pLighting;
	Eegeo::Lighting::GlobalFogging* m_pFogging;
	Eegeo::Lighting::GlobalShadowing* m_pShadowing;
	Eegeo::Rendering::RenderContext* m_pRenderContext;
	Eegeo::iOS::iOSLocationService* m_piOSLocationService;
    Eegeo::Concurrency::Tasks::IGlTaskContextFactory* m_pGlTaskContextFactory;
	iOSUrlEncoder* m_piOSUrlEncoder;
	Eegeo::EegeoWorld* m_pWorld;
	Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider* m_pInterestPointProvider;
	AppInputDelegate* m_pAppInputDelegate;
    AppLocationDelegate* m_pAppLocationDelegate;

	Eegeo::Resources::Terrain::Heights::TerrainHeightRepository m_terrainHeightRepository;
	Eegeo::Resources::Terrain::Heights::TerrainHeightProvider m_terrainHeightProvider;

	Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory m_iOSInputBoxFactory;
	Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory m_iOSKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory m_iOSAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_iOSNativeUIFactories;

	ExampleApp* m_pApp;
	Examples::ExampleController* m_pExampleController;
	Examples::iOSExampleControllerView* m_piOSExampleControllerView;
	Examples::iOSRouteMatchingExampleViewFactory* m_piOSRouteMatchingExampleViewFactory;
	Examples::iOSRouteSimulationExampleViewFactory* m_piOSRouteSimulationExampleViewFactory;
    
    void ConfigureExamples();
	void DestroyExamples();
	void RegisteriOSSpecificExamples();
};

#endif
