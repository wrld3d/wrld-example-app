// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RenderToTextureExampleFactory.h"
#include "RenderToTextureExample.h"

namespace Examples
{
    RenderToTextureExampleFactory::RenderToTextureExampleFactory(Eegeo::EegeoWorld& world,
                                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
    : m_world(world)
    , m_globeCameraController(globeCameraController)
    {
        
    }
    
    IExample* RenderToTextureExampleFactory::CreateExample() const
    {
        return new Examples::RenderToTextureExample(m_globeCameraController,
                                                    m_world.GetRenderContext(),
                                                    m_world.GetVertexLayoutPool(),
                                                    m_world.GetVertexBindingPool(),
                                                    m_world.GetShaderIdGenerator(),
                                                    m_world.GetMaterialIdGenerator(),
                                                    m_world.GetRenderableFilters(),
                                                    m_world.GetGlBufferPool());
    }
    
    std::string RenderToTextureExampleFactory::ExampleName() const
    {
        return Examples::RenderToTextureExample::GetName();
    }
}
