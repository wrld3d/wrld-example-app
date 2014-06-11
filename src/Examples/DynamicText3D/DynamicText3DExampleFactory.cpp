//
//  DynamicText3DExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "DynamicText3DExampleFactory.h"
#include "DynamicText3DExample.h"

using namespace Examples;

DynamicText3DExampleFactory::DynamicText3DExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* DynamicText3DExampleFactory::CreateExample() const
{
	return new Examples::DynamicText3DExample(m_world.GetRenderContext().GetGLState(),
	        m_world.GetCameraProvider(),
	        m_world.GetEnvironmentFlatteningService(),
	        m_world.GetPlaceNameViewBuilder(),
	        m_world,
	        m_globeCameraController);
}

std::string DynamicText3DExampleFactory::ExampleName() const
{
	return Examples::DynamicText3DExample::GetName();
}

