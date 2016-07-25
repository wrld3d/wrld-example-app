// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RenderingTransformMeshModule.h"

#include "ITextureFileLoader.h"
#include "RenderableFilters.h"
#include "RenderingModule.h"
#include "LocalTextureFactory.h"
#include "UnlitTexturedMaterialFactory.h"
#include "TexturedVertexMeshFactory.h"
#include "TransformMeshRenderableFactory.h"
#include "TransformMeshRenderableFilter.h"


namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            RenderingTransformMeshModule::RenderingTransformMeshModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                         Eegeo::Helpers::ITextureFileLoader& textureFileLoader)
            : m_renderableFilters(renderingModule.GetRenderableFilters())
            {
                m_pLocalTextureFactory = Eegeo_NEW(LocalTextureFactory)(textureFileLoader);
                
                m_pUnlitTexturedMaterialFactory = Eegeo_NEW(UnlitTexturedMaterialFactory)(renderingModule.GetMaterialIdGenerator(),
                                                                                                   renderingModule.GetShaderIdGenerator());
                
                m_pTexturedVertexMeshFactory = Eegeo_NEW(TexturedVertexMeshFactory)(renderingModule.GetVertexLayoutPool(),
                                                                                    renderingModule.GetGlBufferPool());
                
                m_pTransformMeshRenderableFactory = Eegeo_NEW(TransformMeshRenderableFactory)(renderingModule.GetVertexBindingPool());
                
                m_pTransformMeshRenderableFilter = Eegeo_NEW(TransformMeshRenderableFilter);
                
                m_renderableFilters.AddRenderableFilter(*m_pTransformMeshRenderableFilter);
            }
            
            RenderingTransformMeshModule::~RenderingTransformMeshModule()
            {
                m_renderableFilters.RemoveRenderableFilter(*m_pTransformMeshRenderableFilter);
                
                Eegeo_DELETE m_pTransformMeshRenderableFilter;
                Eegeo_DELETE m_pTransformMeshRenderableFactory;
                Eegeo_DELETE m_pTexturedVertexMeshFactory;
                Eegeo_DELETE m_pUnlitTexturedMaterialFactory;
                Eegeo_DELETE m_pLocalTextureFactory;
            }
            
            LocalTextureFactory& RenderingTransformMeshModule::GetLocalTextureFactory()
            {
                return *m_pLocalTextureFactory;
            }
            
            UnlitTexturedMaterialFactory& RenderingTransformMeshModule::GetUnlitTexturedMaterialFactory()
            {
                return *m_pUnlitTexturedMaterialFactory;
            }
            
            TexturedVertexMeshFactory& RenderingTransformMeshModule::GetTexturedVertexMeshFactory()
            {
                return *m_pTexturedVertexMeshFactory;
            }
            
            TransformMeshRenderableFactory& RenderingTransformMeshModule::GetTransformMeshRenderableFactory()
            {
                return *m_pTransformMeshRenderableFactory;
            }
            
            TransformMeshRenderableFilter& RenderingTransformMeshModule::GetTransformMeshRenderableFilter()
            {
                return *m_pTransformMeshRenderableFilter;
            }
        }
    }
}