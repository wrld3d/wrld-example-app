//
//  RouteSimulationAnimationExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteSimulationAnimationExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteSimulationAnimationExampleFactory::RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* RouteSimulationAnimationExampleFactory::CreateExample() const
{
    Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory factory(m_world.GetTerrainHeightProvider(),
                                                                                           m_world.GetEnvironmentFlatteningService(),
                                                                                           m_world.GetResourceCeilingProvider(),
                                                                                           m_world.GetCollisionMeshResourceProvider());
    
    return new Examples::RouteSimulationAnimationExample(m_world.GetRouteService(),
                                                         m_world.GetRouteSimulationService(),
                                                         m_world.GetRouteSimulationViewService(),
                                                         m_world.GetCameraProvider(),
                                                         m_world.GetRenderContext().GetGLState(),
                                                         m_world.GetFileIO(),
                                                         m_world.GetLocalAsyncTextureLoader(),
                                                         factory,
                                                         m_world);
}
