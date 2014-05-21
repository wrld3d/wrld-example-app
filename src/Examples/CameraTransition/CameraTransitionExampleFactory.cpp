//
//  CameraTransitionExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "CameraTransitionExampleFactory.h"
#include "CameraTransitionExample.h"

using namespace Examples;

CameraTransitionExampleFactory::CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
                                                               Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* CameraTransitionExampleFactory::CreateExample() const
{
    return new Examples::CameraTransitionExample(m_globeCameraController,
                                                 m_world.GetInterestPointProvider());
}
