// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "AppInterface.h"
#import "ExampleApp.h"
#include "iOSUrlEncoder.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightProvider.h"
#include "TerrainHeightRepository.h"
#include "iOSLocationService.h"
#include "iOSWebRequestService.h"
#include "ExampleController.h"
#include "iOSRouteMatchingExampleViewFactory.h"
#include "iOSRouteSimulationExampleViewFactory.h"
#include "iOSExampleControllerView.h"
#import "External/Reachability/Reachability.h"
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate, CLLocationManagerDelegate>
{

	ExampleApp * m_pExampleApp;
	Examples::iOSExampleControllerView* m_piOSExampleControllerView;
	Examples::ExampleController* m_pExampleController;
	Examples::iOSRouteSimulationExampleViewFactory* m_piOSRouteSimulationExampleViewFactory;
	Examples::iOSRouteMatchingExampleViewFactory* m_piOSRouteMatchingExampleViewFactory;
	Eegeo::Rendering::RenderContext* m_renderContext;
	Eegeo::Blitter* m_pBlitter;
	iOSUrlEncoder iOSUrlEncoder;

	CLLocationManager *locationManager;

	CFTimeInterval previousTimestamp;

	float pixelScale;
	NSTimer* touchTimer;
	Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider* m_pInterestPointProvider;
	Eegeo::iOS::iOSLocationService* piOSLocationService;
	Eegeo::Resources::Terrain::Heights::TerrainHeightRepository m_terrainHeightRepository;
	Eegeo::Resources::Terrain::Heights::TerrainHeightProvider* m_terrainHeightProvider;
	Eegeo::Rendering::EnvironmentFlatteningService* m_pEnvironmentFlatteningService;

	Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory inputBoxFactory;
	Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory keyboardInputFactory;
	Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory alertBoxFactory;
	Eegeo::UI::NativeUIFactories* nativeUIFactories;

	Eegeo::Web::iOSWebRequestService* webRequestService;

	UIRotationGestureRecognizer *gestureRotation;
	UIPinchGestureRecognizer *gesturePinch;
	UIPanGestureRecognizer* gesturePan;
	UITapGestureRecognizer* gestureTap;
	UITapGestureRecognizer* gestureDoubleTap;
	float _previousDist;
}

- (void) initInputs;
- (void) initGraphics;
- (void) initWorld;
- (void) update;

@end
