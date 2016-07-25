// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Helpers.h"
#include "Modules.h"
#include "Rendering.h"
#include "Types.h"
#include "RenderingTransformMesh.h"


namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class RenderingTransformMeshModule : Eegeo::NonCopyable
            {
            private:
                LocalTextureFactory* m_pLocalTextureFactory;
                UnlitTexturedMaterialFactory* m_pUnlitTexturedMaterialFactory;
                TexturedVertexMeshFactory* m_pTexturedVertexMeshFactory;
                TransformMeshRenderableFactory* m_pTransformMeshRenderableFactory;
                TransformMeshRenderableFilter* m_pTransformMeshRenderableFilter;
                Eegeo::Rendering::RenderableFilters& m_renderableFilters;
                
            public:
                RenderingTransformMeshModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                             Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
                
                ~RenderingTransformMeshModule();
                
                LocalTextureFactory& GetLocalTextureFactory();
                
                UnlitTexturedMaterialFactory& GetUnlitTexturedMaterialFactory();
                
                TexturedVertexMeshFactory& GetTexturedVertexMeshFactory();
                
                TransformMeshRenderableFactory& GetTransformMeshRenderableFactory();
                
                TransformMeshRenderableFilter& GetTransformMeshRenderableFilter();
            };
        }
    }
}