// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleApp.h"
#include "GlobeCameraTouchController.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"
#include "LatLongAltitude.h"

//example factories
#include "CameraTransitionExampleFactory.h"
#include "ControlCityThemeExampleFactory.h"
#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugSphereExampleFactory.h"
#include "DynamicText3DExampleFactory.h"
#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentNotifierExampleFactory.h"
#include "FileIOExampleFactory.h"
#include "LoadModelExampleFactory.h"
#include "ModifiedRenderingExampleFactory.h"
#include "NavigationGraphExampleFactory.h"
#include "Pick3DObjectExampleFactory.h"
#include "PinOverModelExampleFactory.h"
#include "PinsExampleFactory.h"
#include "PODAnimationExampleFactory.h"
#include "ResourceSpatialQueryExampleFactory.h"
#include "RouteDrawingExampleFactory.h"
#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteThicknessPolicyExampleFactory.h"
#include "ScreenPickExampleFactory.h"
#include "ScreenUnprojectExampleFactory.h"
#include "SingleCityExampleFactory.h"
#include "ToggleTrafficExampleFactory.h"
#include "TrafficCongestionExampleFactory.h"
#include "WebRequestExampleFactory.h"


ExampleApp::ExampleApp(Eegeo::EegeoWorld* pWorld,
                       Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& globeCameraInterestPointProvider,
                       Examples::ExampleController& exampleController)
	: m_pGlobeCameraController(NULL)
	, m_pCameraTouchController(NULL)
	, m_globeCameraInterestPointProvider(globeCameraInterestPointProvider)
	, m_pWorld(pWorld)
	, m_exampleController(exampleController)
{
	Eegeo_ASSERT(&m_globeCameraInterestPointProvider != NULL);

	Eegeo::EegeoWorld& eegeoWorld = *pWorld;

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();

	// override default configuration to enable two-finger pan gesture to control additional camera pitch
	touchControllerConfig.tiltEnabled = true;

	m_pCameraTouchController = new Eegeo::Camera::GlobeCamera::GlobeCameraTouchController(touchControllerConfig);

	const bool useLowSpecSettings = false;
	Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);

	m_pGlobeCameraController = new Eegeo::Camera::GlobeCamera::GlobeCameraController(eegeoWorld.GetTerrainHeightProvider(),
	        eegeoWorld.GetEnvironmentFlatteningService(),
	        eegeoWorld.GetResourceCeilingProvider(),
	        *m_pCameraTouchController,
	        globeCameraControllerConfig);

	Eegeo::Camera::RenderCamera* renderCamera = m_pGlobeCameraController->GetCamera();
	const Eegeo::Rendering::RenderContext& renderContext = eegeoWorld.GetRenderContext();
	renderCamera->SetViewport(0.f, 0.f, renderContext.GetScreenWidth(), renderContext.GetScreenHeight());
	eegeoWorld.SetCamera(renderCamera);

	m_globeCameraInterestPointProvider.SetGlobeCamera(m_pGlobeCameraController);

	float interestPointLatitudeDegrees = 37.7858f;
	float interestPointLongitudeDegrees = -122.401f;
	float interestPointAltitudeMeters = 2.7;

	Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(interestPointLatitudeDegrees,
	        interestPointLongitudeDegrees,
	        interestPointAltitudeMeters);

	float cameraControllerOrientationDegrees = 0.0f;
	float cameraControllerDistanceFromInterestPointMeters = 1781.0f;

	Eegeo::Space::EcefTangentBasis cameraInterestBasis;
	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);

	m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);

	//register all generic examples
	m_exampleController.RegisterCameraExample<Examples::CameraTransitionExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ControlCityThemeExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::DebugPrimitiveRenderingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::DebugSphereExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::DynamicText3DExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::EnvironmentFlatteningExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::EnvironmentNotifierExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::FileIOExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::LoadModelExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ModifiedRenderingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::NavigationGraphExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::Pick3DObjectExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PinsExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PinOverModelExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PODAnimationExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ResourceSpatialQueryExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteDrawingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteSimulationAnimationExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteThicknessPolicyExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ScreenPickExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ScreenUnprojectExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::SingleCityExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ToggleTrafficExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::TrafficCongestionExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::WebRequestExampleFactory>(*m_pGlobeCameraController);
}

ExampleApp::~ExampleApp()
{
	delete m_pGlobeCameraController;
	delete m_pCameraTouchController;
}

void ExampleApp::OnPause()
{

}

void ExampleApp::OnResume()
{

}

void ExampleApp::Update (float dt)
{
	Eegeo::EegeoWorld& eegeoWorld = World();

	eegeoWorld.EarlyUpdate(dt);
	m_exampleController.EarlyUpdate(dt, *m_pGlobeCameraController, *m_pCameraTouchController);

	eegeoWorld.Update(dt);
	m_exampleController.Update(dt);
}

void ExampleApp::Draw (float dt)
{
	Eegeo::Rendering::GLState& glState = World().GetRenderContext().GetGLState();
	glState.ClearColor(0.8f, 0.8f, 0.8f, 1.f);
	World().Draw(dt);
	m_exampleController.Draw();
}

void ExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
{
	if(!m_exampleController.Event_TouchRotate(data))
	{
		m_pCameraTouchController->Event_TouchRotate(data);
	}
}

void ExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
	if(!m_exampleController.Event_TouchRotate_Start(data))
	{
		m_pCameraTouchController->Event_TouchRotate_Start(data);
	}
}

void ExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
	if(!m_exampleController.Event_TouchRotate_End(data))
	{
		m_pCameraTouchController->Event_TouchRotate_End(data);
	}
}

void ExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
{
	if(!m_exampleController.Event_TouchPinch(data))
	{
		m_pCameraTouchController->Event_TouchPinch(data);
	}
}

void ExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
	if(!m_exampleController.Event_TouchPinch_Start(data))
	{
		m_pCameraTouchController->Event_TouchPinch_Start(data);
	}
}

void ExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
	if(!m_exampleController.Event_TouchPinch_End(data))
	{
		m_pCameraTouchController->Event_TouchPinch_End(data);
	}
}

void ExampleApp::Event_TouchPan(const AppInterface::PanData& data)
{
	if(!m_exampleController.Event_TouchPan(data))
	{
		m_pCameraTouchController->Event_TouchPan(data);
	}
}

void ExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
{
	if(!m_exampleController.Event_TouchPan_Start(data))
	{
		m_pCameraTouchController->Event_TouchPan_Start(data);
	}
}

void ExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
{
	if(!m_exampleController.Event_TouchPan_End(data))
	{
		m_pCameraTouchController->Event_TouchPan_End(data);
	}
}

void ExampleApp::Event_TouchTap(const AppInterface::TapData& data)
{
	if(!m_exampleController.Event_TouchTap(data))
	{
		m_pCameraTouchController->Event_TouchTap(data);
	}
}

void ExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
	if(!m_exampleController.Event_TouchDoubleTap(data))
	{
		m_pCameraTouchController->Event_TouchDoubleTap(data);
	}
}

void ExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
{
	if(!m_exampleController.Event_TouchDown(data))
	{
		m_pCameraTouchController->Event_TouchDown(data);
	}
}

void ExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
{
	if(!m_exampleController.Event_TouchMove(data))
	{
		m_pCameraTouchController->Event_TouchMove(data);
	}
}

void ExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
{
	if(!m_exampleController.Event_TouchUp(data))
	{
		m_pCameraTouchController->Event_TouchUp(data);
	}
}

