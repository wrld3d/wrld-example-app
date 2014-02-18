//
//  RouteSimulationAnimationExample.cpp
//  ExampleApp
//
//  Created by Ian Hutchinson on 18/02/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteSimulationAnimationExample.h"
#include "VectorMath.h"
#include "GlobeCameraTouchControllerConfiguration.h"

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
                                               Eegeo::Rendering::GLState& glState,
                                               Eegeo::Helpers::IFileIO& fileIO,
                                               Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                               RouteSimulationGlobeCameraControllerFactory routeSimulationGlobeCameraControllerFactory,
                                               EegeoWorld& world)
:m_routeService(routeService)
,m_routeSimulationService(routeSimulationService)
,m_routeSimulationViewService(routeSimulationViewService)
,m_glState(glState)
,m_fileIO(fileIO)
,m_textureLoader(textureLoader)
,m_routeSimulationGlobeCameraControllerFactory(routeSimulationGlobeCameraControllerFactory)
,m_world(world)
,m_initialised(false)
,m_route(NULL)
,m_pModel(NULL)
,m_modelAnimationSpeed(1.f/30.f)
,m_pSessionCamera(NULL)
,m_pViewBindingForCameraSession(NULL)
,m_pRouteSessionFollowCameraController(NULL)
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
    m_route = BuildRoute();
    
    m_pSessionCamera = m_routeSimulationService.BeginRouteSimulationSession(*m_route);
    
    //Create a local transform for the views which will be bound to the route simulation
    //session.
    Eegeo::m44 scale, rotation, transform;
    scale.Scale(3.f);
    rotation.RotateY(M_PI);
    m44::Mul(transform, scale, rotation);
    
    m_pViewBindingForCameraSession = m_routeSimulationViewService.CreateBinding(*m_pSessionCamera, pCharacter, transform);
    
    m_pSessionCamera->StartPlaybackFromBeginning();
    
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfiguration = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
    touchConfiguration.tiltEnabled = true;
    
    m_pRouteSessionFollowCameraController = m_routeSimulationGlobeCameraControllerFactory.Create(false, *m_pSessionCamera, touchConfiguration);
    m_pRouteSessionFollowCameraController->SetView(37.7858, -122.401, 0, 781.0f);
    m_pRouteSessionFollowCameraController->StartFollowingSession();
    
}

void RouteSimulationAnimationExample::EarlyUpdate(float dt)
{
    //Defer initialisation until the loading state is over.
    if(m_world.Initialising()) {
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
    if(!m_initialised) {
        return;
    }
    
    if(m_pSessionCamera->IsRouteCompleted())
    {
        m_pSessionCamera->TogglePlaybackDirection();
        m_pSessionCamera->Unpause();
    }
    
    //Update animation
    //For this walking animation, the animation speed scales
    //with the speed of the route (See line 155)
    m_pModel->UpdateAnimator(m_modelAnimationSpeed);
}

void RouteSimulationAnimationExample::Suspend()
{

    m_routeSimulationViewService.DestroyBinding(m_pViewBindingForCameraSession);
    
    m_routeSimulationService.EndRouteSimulationSession(m_pSessionCamera);
    
    m_pSessionCamera = NULL;
    
    m_routeService.DestroyRoute(m_route);
    m_route = NULL;
    
    delete m_pModel;
    m_pModel = NULL;
    
    delete m_pRouteSessionFollowCameraController;
    m_pRouteSessionFollowCameraController = NULL;
    
    m_initialised = false;
}

Route* RouteSimulationAnimationExample::BuildRoute()
{
    const float halfWidth = 5.f;
    
    // 0.00185 is a factor that works well for the animation
    // speed of this model
    const float routeSpeedMetersPerSecond = 30.f;
    m_modelAnimationSpeed = routeSpeedMetersPerSecond * 0.00185;
    
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
    
    const Eegeo::Routes::Style::RouteStyle style(Eegeo::Routes::Style::RouteStyle::JoinStyleArc, m_routeThicknessPolicy);
    return m_routeService.CreateRoute(points, style, false);
}

Eegeo::Model* RouteSimulationAnimationExample::LoadCharacterModel(Eegeo::Node*& pCharacter) const
{
    Eegeo::Model* pModel = new Eegeo::Model(m_glState, m_textureLoader, m_fileIO);
    pModel->Load("BoxCharacter.pod");
    Eegeo_ASSERT(pModel->GetRootNode());
    
    pCharacter = pModel->GetRootNode();
    
    return pModel;
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