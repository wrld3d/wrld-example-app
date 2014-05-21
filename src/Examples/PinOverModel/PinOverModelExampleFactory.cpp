//
//  PinOverModelExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "PinOverModelExampleFactory.h"
#include "PinOverModelExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

PinOverModelExampleFactory::PinOverModelExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* PinOverModelExampleFactory::CreateExample() const
{
    return new Examples::PinOverModelExample(m_world.GetTextureLoader(),
                                             m_world.GetGlBufferPool(),
                                             m_world.GetShaderIdGenerator(),
                                             m_world.GetMaterialIdGenerator(),
                                             m_world.GetVertexBindingPool(),
                                             m_world.GetVertexLayoutPool(),
                                             m_world.GetRenderableFilters(),
                                             m_world.GetCameraProvider(),
                                             m_world.GetTerrainHeightProvider(),
                                             m_world.GetEnvironmentFlatteningService(),
                                             m_world.GetRenderContext(),
                                             m_world.GetFileIO(),
                                             m_world.GetLocalAsyncTextureLoader(),
                                             m_world.GetGlobalFogging(),
                                             m_world.GetNullMaterial());
}
