//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef APPHOST_H_
#define APPHOST_H_

#include "Types.h"
#include "Graphics.h"
#include "AndroidFileIO.h"
#include "AndroidHttpCache.h"
#include "AndroidTextureFileLoader.h"
#include "AndroidWebRequestService.hpp"
#include "AndroidTaskQueue.h"
#include "AndroidWebLoadRequestFactory.h"
#include "AndroidInputProcessor.h"
#include "AndroidLocationService.h"
#include "AndroidUrlEncoder.h"
#include "GlobeCameraInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "AndroidInputHandler.h"
#include "AndroidInputBoxFactory.h"
#include "AndroidKeyboardInputFactory.h"
#include "AndroidAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightRepository.h"
#include "GlobalShadowing.h"
#include "TouchEventWrapper.h"
#include "Blitter.h"
#include "IAndroidTouchInputHandler.h"
#include "AppToJavaProxy.h"
#include "AndroidNativeState.h"
#include "AppInputDelegate.h"
#include <vector>

//example app includes
#include "ExampleApp.h"
#include "ExampleController.h"
#include "UiThreadToNativeThreadTaskQueue.h"
#include "AndroidRouteMatchingExampleViewFactory.h"
#include "AndroidRouteSimulationExampleViewFactory.h"
#include "ExampleCameraJumpController.h"

class AppHost :
	public IAndroidTouchInputHandler,
	protected Eegeo::NonCopyable
{
public:
	AppHost(
			const std::string& apiKey,
			AndroidNativeState& nativeState,
			float displayWidth,
			float displayHeight,
		    EGLDisplay display,
		    EGLSurface shareSurface,
		    EGLContext resourceBuildShareContext,
		    AppToJavaProxy& appToJavaProxy
			);
	~AppHost();

	void Update(float dt);
	void Draw(float dt);

	void OnPause();
	void OnResume();

	void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

	void SetEnvironmentFlatten(bool flattenState);
	void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
	void SendCameraLocationToGUI();

	// Suspect.
	void SetSharedSurface(EGLSurface sharedSurface);
	void SetViewportOffset(float x, float y);

private:
	Eegeo::Android::AndroidTaskQueue* m_pTaskQueue;
	Eegeo::Rendering::EnvironmentFlatteningService* m_pEnvironmentFlatteningService;
	Eegeo::Android::AndroidWebLoadRequestFactory* m_pAndroidWebLoadRequestFactory;
	Eegeo::Android::AndroidWebRequestService* m_pAndroidWebRequestService;
	Eegeo::Blitter* m_pBlitter;
	Eegeo::Android::AndroidTextureFileLoader* m_pTextureLoader;
	Eegeo::Android::AndroidHttpCache* m_pHttpCache;
	Eegeo::Android::AndroidFileIO* m_pFileIO;
	Eegeo::Lighting::GlobalLighting* m_pLighting;
	Eegeo::Lighting::GlobalFogging* m_pFogging;
	Eegeo::Lighting::GlobalShadowing* m_pShadowing;
	Eegeo::Rendering::RenderContext* m_pRenderContext;
	Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
	Eegeo::Android::AndroidUrlEncoder* m_pAndroidUrlEncoder;
	Eegeo::EegeoWorld* m_pWorld;
	AndroidNativeState& m_nativeState;
	Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider* m_pInterestPointProvider;
	AppInputDelegate* m_pAppInputDelegate;

    Eegeo::Resources::Terrain::Heights::TerrainHeightRepository m_terrainHeightRepository;
    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider m_terrainHeightProvider;

	Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
	Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
	Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

	ExampleApp* m_pApp;
	Examples::ExampleController* m_pExampleController;
	UiThreadToNativeThreadTaskQueue m_uiThreadToNativeThreadTaskQueue;
	Examples::AndroidRouteMatchingExampleViewFactory* m_pAndroidRouteMatchingExampleViewFactory;
	Examples::AndroidRouteSimulationExampleViewFactory* m_pAndroidRouteSimulationExampleViewFactory;
	ExampleCameraJumpController* m_pExampleCameraJumpController;

	Eegeo::Android::Input::AndroidInputProcessor* m_pInputProcessor;

    AppToJavaProxy& m_appToJavaProxy;

    void RegisterAndroidSpecificExamples();
    void DestroyAndroidSpecificExamples();
};

#endif
