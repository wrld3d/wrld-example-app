// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"

#include <set>
#include "Types.h"
#include "TransformMeshRenderable.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class TransformMeshRenderableFilter : public Eegeo::Rendering::IRenderableFilter, Eegeo::NonCopyable
            {
            private:
                std::set<TransformMeshRenderable*> m_transformMeshRenderables;
            public:
                
                void AddTransformMeshRenderable(TransformMeshRenderable& transformMeshRenderable);
                
                void RemoveTransformMeshRenderable(TransformMeshRenderable& transformMeshRenderable);
                
                // IRenderableFilter
                
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            };
        }
    }
}