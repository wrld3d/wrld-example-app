// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TransformMeshRenderableFilter.h"

#include "RenderCamera.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            namespace
            {
                inline Eegeo::m44 CreateTranslationMatrix(const Eegeo::dv3& ecefRenderablePosition, const Eegeo::dv3& ecefCameraPosition)
                {
                    Eegeo::v4 cameraRelativeModelOrigin((ecefRenderablePosition - ecefCameraPosition).ToSingle(),1.0f);
                    Eegeo::m44 translation = Eegeo::m44::CreateIdentity();;
                    translation.SetRow(3, cameraRelativeModelOrigin);
                    return translation;
                }
            }
            
            void TransformMeshRenderableFilter::AddTransformMeshRenderable(TransformMeshRenderable& transformMeshRenderable)
            {
                if(m_transformMeshRenderables.find(&transformMeshRenderable) != m_transformMeshRenderables.end())
                {
                    Eegeo_TTY("Warning: Ignoring adding a TransformMeshRenderable that is already in filter");
                    return;
                }
                m_transformMeshRenderables.insert(&transformMeshRenderable);
            }
            
            void TransformMeshRenderableFilter::RemoveTransformMeshRenderable(TransformMeshRenderable& transformMeshRenderable)
            {
                if(m_transformMeshRenderables.find(&transformMeshRenderable) == m_transformMeshRenderables.end())
                {
                    Eegeo_TTY("Warning: Ignoring removing a TransformMeshRenderable that is not in filter");
                    return;
                }
                m_transformMeshRenderables.erase(&transformMeshRenderable);
            }
            
            void TransformMeshRenderableFilter::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
            {
                const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
                
                const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
                const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
                
                for(std::set<TransformMeshRenderable*>::iterator it = m_transformMeshRenderables.begin(); it != m_transformMeshRenderables.end(); ++it)
                {
                    TransformMeshRenderable* renderable = *it;
                    
                    Eegeo::m44 translation = CreateTranslationMatrix(renderable->GetEcefPosition(), ecefCameraPosition);
                    
                    Eegeo::m44 transformToCamera;
                    Eegeo::m44::Mul(transformToCamera, translation, renderable->GetTransform());
                    
                    Eegeo::m44 mvp;
                    Eegeo::m44::Mul(mvp, viewProjection, transformToCamera);
                    
                    renderable->SetModelViewProjection(mvp);
                    
                    renderQueue.EnqueueRenderable(renderable);
                }
            }
        }
    }
}