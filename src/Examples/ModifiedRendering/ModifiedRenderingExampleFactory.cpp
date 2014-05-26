//
//  ModifiedRenderingExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ModifiedRenderingExampleFactory.h"
#include "ModifiedRenderingExample.h"

using namespace Examples;

ModifiedRenderingExampleFactory::ModifiedRenderingExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* ModifiedRenderingExampleFactory::CreateExample() const
{
    return new Examples::ModifiedRenderingExample(m_world.GetRenderContext(),
                                                  m_world.GetCameraProvider(),
                                                  m_world.GetInterestPointProvider(),
                                                  m_world.GetStreamingVolume(),
                                                  m_world.GetGlobalLighting(),
                                                  m_world.GetBuildingSceneElementRepository(),
                                                  m_world.GetBuildingsRenderableFilter(),
                                                  m_world.GetRenderQueue(),
                                                  m_world.GetRenderableFilters(),
                                                  m_world.GetShaderIdGenerator(),
                                                  m_world.GetMaterialIdGenerator(),
                                                  m_world.GetEnvironmentPlaceholderTexture());
}

std::string ModifiedRenderingExampleFactory::ExampleName() const
{
	return Examples::ModifiedRenderingExample::GetName();
}

