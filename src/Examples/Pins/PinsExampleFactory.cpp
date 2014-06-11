//
//  PinsExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "PinsExampleFactory.h"
#include "PinsExample.h"

using namespace Examples;

PinsExampleFactory::PinsExampleFactory(Eegeo::EegeoWorld& world,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PinsExampleFactory::CreateExample() const
{
	return new Examples::PinsExample(m_world.GetTextureLoader(),
	                                 m_world.GetGlBufferPool(),
	                                 m_world.GetShaderIdGenerator(),
	                                 m_world.GetMaterialIdGenerator(),
	                                 m_world.GetVertexBindingPool(),
	                                 m_world.GetVertexLayoutPool(),
	                                 m_world.GetRenderableFilters(),
	                                 m_world.GetCameraProvider(),
	                                 m_world.GetTerrainHeightProvider(),
	                                 m_world.GetEnvironmentFlatteningService(),
	                                 m_globeCameraController);
}

std::string PinsExampleFactory::ExampleName() const
{
	return Examples::PinsExample::GetName();
}

