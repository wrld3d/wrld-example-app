//
//  PODAnimationExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "PODAnimationExampleFactory.h"
#include "PODAnimationExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

PODAnimationExampleFactory::PODAnimationExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PODAnimationExampleFactory::CreateExample() const
{
	return new Examples::PODAnimationExample(m_world.GetRenderContext(),
	        m_world.GetFileIO(),
	        m_world.GetLocalAsyncTextureLoader(),
	        m_world.GetGlobalFogging(),
	        m_globeCameraController);
}

std::string PODAnimationExampleFactory::ExampleName() const
{
	return Examples::PODAnimationExample::GetName();
}

