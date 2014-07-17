// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationAnimationExample.h"
#include "VectorMath.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "TransformHelpers.h"
#include "ICameraProvider.h"

using namespace Examples;
using namespace Eegeo;
using namespace Eegeo::Routes;
using namespace Eegeo::Routes::Simulation;
using namespace Eegeo::Routes::Simulation::View;
using namespace Eegeo::Routes::Simulation::Camera;

RouteSimulationAnimationExample::RouteSimulationAnimationExample(
    RouteService& routeService,
    RouteSimulationService& routeSimulationService,
    RouteSimulationViewService& routeSimulationViewService,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& defaultCamera,
    Eegeo::Camera::ICameraProvider& cameraProvider,
    Eegeo::Rendering::GLState& glState,
    Eegeo::Helpers::IFileIO& fileIO,
    Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
    RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
    EegeoWorld& world)
	:m_routeService(routeService)
	,m_routeSimulationService(routeSimulationService)
	,m_routeSimulationViewService(routeSimulationViewService)
	,m_defaultCamera(defaultCamera)
	,m_cameraProvider(cameraProvider)
	,m_glState(glState)
	,m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
	,m_routeSimulationGlobeCameraControllerFactory(routeSimulationGlobeCameraControllerFactory)
	,m_world(world)
	,m_initialised(false)
	,m_pRoute(NULL)
	,m_pModel(NULL)
	,m_modelAnimationSpeed(1.f/30.f)
	,m_pRouteSimulationSession(NULL)
	,m_pViewBindingForCameraSession(NULL)
	,m_pRouteSessionFollowCameraController(NULL)
	,m_globeCameraStateRestorer(defaultCamera)
{
}

void RouteSimulationAnimationExample::Initialise()
{
	//Load a model containing the node that will be bound to our route simulation session. For
	//a detailed explation see http://sdk.eegeo.com/developers/mobiledocs/loading_rendering_models
	//or see LoadModelExample.cpp.
	Eegeo::Node *pCharacter;
	m_pModel = LoadCharacterModel(pCharacter);

	//Build the route - see RouteDrawingExample.cpp for a detailed explanation of building routes, or
	//check out http://sdk.eegeo.com/developers/mobiledocs/routes
	m_pRoute = BuildRoute();

	m_pRouteSimulationSession = m_routeSimulationService.BeginRouteSimulationSession(*m_pRoute);

	Eegeo::m44 transform;
	CalculateTransform(transform);

	m_pViewBindingForCameraSession = m_routeSimulationViewService.CreateBinding(*m_pRouteSimulationSession, pCharacter, transform);

	m_pRouteSimulationSession->StartPlaybackFromBeginning();

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfiguration = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
	touchConfiguration.tiltEnabled = true;

	RouteSimulationGlobeCameraControllerConfig routeSimCameraConfig = RouteSimulationGlobeCameraControllerConfig::CreateDefault();

	m_pRouteSessionFollowCameraController = m_routeSimulationGlobeCameraControllerFactory.Create(false, touchConfiguration, routeSimCameraConfig);
	m_pRouteSessionFollowCameraController->SetView(37.7858, -122.401, 0, 781.0f);
	m_pRouteSessionFollowCameraController->StartFollowingSession(m_pRouteSimulationSession);

}

void RouteSimulationAnimationExample::EarlyUpdate(float dt)
{
	//Defer initialisation until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}

	//Just create the routes once.
	if(!m_initialised)
	{
		//Load the model, build the route, create and configure the simulation settings.
		Initialise();

		//We have initialised so don't need to do so again.
		m_initialised = true;
	}

	m_pRouteSessionFollowCameraController->Update(dt);
	m_world.SetCamera(m_pRouteSessionFollowCameraController->GetCamera());

}

void RouteSimulationAnimationExample::Update(float dt)
{
	//Defer initialisation until the loading state is over.
	if(!m_initialised)
	{
		return;
	}

	if(m_pRouteSimulationSession->IsRouteCompleted())
	{
		m_pRouteSimulationSession->TogglePlaybackDirection();
		m_pRouteSimulationSession->Unpause();
	}

	Eegeo_TTY("%f metres from start of route. %f percent.\n", m_pRouteSimulationSession->GetDistanceFromStartInMetres(),(m_pRouteSimulationSession->GetDistanceFromStartInMetres() / m_pRoute->GetLength())*100.0f);

	Eegeo::m44 transform;
	CalculateTransform(transform);
	m_pViewBindingForCameraSession->SetModelTransform(transform);

	//Update animation
	//For this walking animation, the animation speed scales
	//with the speed of the route (See line 155)
	m_pModel->UpdateAnimator(m_modelAnimationSpeed);
}

void RouteSimulationAnimationExample::Suspend()
{
	if (m_pRouteSessionFollowCameraController)
	{
		m_pRouteSessionFollowCameraController->StopFollowingSession();
	}

	m_routeSimulationViewService.DestroyBinding(m_pViewBindingForCameraSession);

	m_routeSimulationService.EndRouteSimulationSession(m_pRouteSimulationSession);

	m_pRouteSimulationSession = NULL;

	m_routeService.DestroyRoute(m_pRoute);
	m_pRoute = NULL;

	delete m_pModel;
	m_pModel = NULL;

	delete m_pRouteSessionFollowCameraController;
	m_pRouteSessionFollowCameraController = NULL;

	m_world.SetCamera(m_defaultCamera.GetCamera());

	m_initialised = false;
}

Route* RouteSimulationAnimationExample::BuildRoute()
{
	const float halfWidth = 5.f;

	// 0.00185 is a factor that works well for the animation
	// speed of this model
	const float routeSpeedMetersPerSecond = 30.f;
	m_modelAnimationSpeed = routeSpeedMetersPerSecond * 0.00185f;

	const Eegeo::v4 routeColor(1, 0, 1, 0.6f);
	const float altitudeMeters = 3.f;

	RouteBuilder builder;

	std::vector<RouteVertex> points = builder.Start(routeColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
	                                  .AddPoint(37.795729,-122.401698, altitudeMeters)
	                                  .AddPoint(37.794873,-122.401516, altitudeMeters)
	                                  .AddPoint(37.794728,-122.403179, altitudeMeters)
	                                  .AddPoint(37.794483,-122.404863, altitudeMeters)
	                                  .AddPoint(37.793618,-122.404670, altitudeMeters)
	                                  .AddPoint(37.793813,-122.403007, altitudeMeters)
	                                  .AddPoint(37.792940,-122.402825, altitudeMeters)
	                                  .AddPoint(37.793109,-122.401108, altitudeMeters)
	                                  .AddPoint(37.792143,-122.400990, altitudeMeters)
	                                  .AddPoint(37.790303,-122.400603, altitudeMeters)
	                                  .AddPoint(37.790324,-122.400126, altitudeMeters)
	                                  .AddPoint(37.794449,-122.394906, altitudeMeters)
	                                  .AddPoint(37.793253,-122.393238, altitudeMeters)
	                                  .AddPoint(37.793707,-122.392578, altitudeMeters)
	                                  .FinishRoute();

	const Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
	return m_routeService.CreateRoute(points, routeStyle, false);
}

Eegeo::Model* RouteSimulationAnimationExample::LoadCharacterModel(Eegeo::Node*& pCharacter) const
{
	Eegeo::Model* pModel = Eegeo::Model::CreateFromPODFile("route_simulation_animation_example/BoxCharacter.pod", m_fileIO, m_glState, &m_textureRequestor, "route_simulation_animation_example/");
	Eegeo_ASSERT(pModel->GetRootNode());

	pCharacter = pModel->GetRootNode();

	return pModel;
}

void RouteSimulationAnimationExample::CalculateTransform(Eegeo::m44& transform)
{
	const float scaleModifier = 100.f;
	const float minimumScale = 3.f;

	const Eegeo::dv3& position = m_pRouteSimulationSession->GetCurrentPositionEcef();
	float scaleAsFunctionOfAltitude = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(
	                                      m_cameraProvider.GetRenderCamera(),
	                                      position
	                                  ) / scaleModifier;
	Eegeo::m44 scale, rotation;
	scale.Scale(Eegeo::Max(scaleAsFunctionOfAltitude, minimumScale));
	rotation.RotateY(static_cast<float>(M_PI));
	m44::Mul(transform, scale, rotation);

}


bool RouteSimulationAnimationExample::Event_TouchRotate(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_Start(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_End(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPinch(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_Start(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_End(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPan(const AppInterface::PanData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPan_Start(const AppInterface::PanData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_Start(data);
	return true;
}

bool RouteSimulationAnimationExample::Event_TouchPan_End(const AppInterface::PanData& data)
{

	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_End(data);
	return true;
}
