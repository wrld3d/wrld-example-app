// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingRenderable.h"
#include "LayerIds.h"
#include "NullMaterial.h"
#include "Node.h"
#include "RenderCamera.h"
#include "RenderingModule.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Quad.h"
#include "VertexBindingPool.h"
#include "Mesh.h"
#include "WorldMeshRenderable.h"
#include "SpherePrimitive.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingRenderable::PoiRingRenderable(Eegeo::Modules::Core::RenderingModule& renderingModule)
                    : Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::AfterAll,
                                                       Eegeo::dv3::Zero(),
                                                       &renderingModule.GetNullMaterial())
                    , m_innerSphereScale(165.f)
                {
                    // Don't take in rendering module:
                    // Needs: ShaderIDGenerator, MaterialIDGenerator, GLBufferPool, VertexLayoutPool, VertexBindingPool, PositionMeshFactory, NullMaterial

                    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                    m_pColorShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());

                    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                    m_pColorMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::ColorMaterial)(materialIdGenerator.GetNextId(),
                                       "RingQuadStencilMat",
                                       *m_pColorShader,
                                       Eegeo::v4(1.f, 1.f, 1.f, 1.f));

                    Eegeo::Rendering::Mesh* pQuadMesh = Eegeo::Rendering::Geometry::CreatePositionQuad(renderingModule.GetGlBufferPool(),
                                                        renderingModule.GetVertexLayoutPool());

                    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = renderingModule.GetVertexBindingPool();
                    const Eegeo::Rendering::VertexLayouts::VertexBinding& quadVertexBinding = vertexBindingPool.GetVertexBinding(pQuadMesh->GetVertexLayout(),
                            m_pColorShader->GetVertexAttributes());

                    m_pQuadRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                        m_pColorMaterial,
                                        quadVertexBinding,
                                        pQuadMesh,
                                        Eegeo::dv3::Zero());
                    m_pQuadRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

                    std::vector<Eegeo::v3> sphereVerts;
                    std::vector<u16> sphereIndices;
                    Eegeo::Rendering::Geometry::BuildUnitSphere(sphereVerts, sphereIndices, 8);
                    
                    Eegeo::Rendering::MeshFactories::PositionMeshFactory& meshFactory = renderingModule.GetPositionMeshFactory();
                    Eegeo::Rendering::Mesh* pSphereMesh = meshFactory.CreateMesh(sphereVerts, sphereIndices, "sphere");

                    const Eegeo::Rendering::VertexLayouts::VertexBinding& sphereVertexBinding = vertexBindingPool.GetVertexBinding(pSphereMesh->GetVertexLayout(),
                        m_pColorShader->GetVertexAttributes());
                    m_pSphereRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                        m_pColorMaterial,
                        sphereVertexBinding,
                        pSphereMesh,
                        Eegeo::dv3::Zero());
                    m_pSphereRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

                }

                PoiRingRenderable::~PoiRingRenderable()
                {
                    Eegeo_DELETE m_pSphereRenderable;
                    Eegeo_DELETE m_pQuadRenderable;
                    Eegeo_DELETE m_pColorMaterial;
                    Eegeo_DELETE m_pColorShader;
                }

                void PoiRingRenderable::Render(Eegeo::Rendering::GLState &glState) const
                {
                    // Note: This renderable has quite unique behaviour, given the masking
                    //       techniques it uses. It should not be used as a reference for
                    //       common use of the renderable pattern. Please see the examples
                    //       at https://github.com/eegeo/mobile-sdk-harness for correct usage.
                    RenderClearStencil(glState);
                    RenderSpheres(glState);
                    RenderRingEffects(glState);
                }

                void PoiRingRenderable::RenderClearStencil(Eegeo::Rendering::GLState& glState) const
                {
                    m_pColorMaterial->SetState(glState);

                    glState.DepthMask(GL_FALSE);
                    glState.DepthTest.Enable();
                    glState.DepthFunc(GL_ALWAYS);
                    glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                    glState.Blend.Disable();
                    glState.StencilTest.Enable();
                    glState.StencilFunc(GL_ALWAYS, 0, 0xFF);
                    glState.StencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

                    m_pQuadRenderable->Render(glState);
                }

                void PoiRingRenderable::RenderSpheres(Eegeo::Rendering::GLState &glState) const
                {
                    glState.BindTexture2D(0);
                    glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

                    glState.DepthMask(GL_FALSE);
                    glState.DepthTest.Enable();
                    glState.DepthFunc(GL_LESS);

                    glState.CullFace.Disable();

                    glState.StencilTest.Enable();
                    glState.StencilFunc(GL_ALWAYS, 1, 0xFF);
                    glState.StencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
                    glState.StencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP);

                    m_pSphereRenderable->Render(glState);

                    const Eegeo::v4 originalCameraRelativePosition = m_modelTransform.GetRow(3);
                    Eegeo::m44 transform;
                    Eegeo::m44 mvp;
                    transform.Scale(m_innerSphereScale);
                    transform.SetRow(3, originalCameraRelativePosition);
                    Eegeo::m44::Mul(mvp, m_viewProjection, transform);
                    m_pSphereRenderable->SetModelViewProjection(mvp);
                    m_pSphereRenderable->Render(glState);
                }

                void PoiRingRenderable::RenderRingEffects(Eegeo::Rendering::GLState &glState) const
                {
                    m_pColorMaterial->SetState(glState);

                    Eegeo::v4 ringColor = Eegeo::v4(1.f, 1.f, 1.f, 0.9f);
                    m_pColorMaterial->SetColor(ringColor);

                    glState.StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                    glState.ColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                    glState.StencilFunc(GL_EQUAL, 1, 0xFF);
                    glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glState.BlendEquation(GL_FUNC_ADD);

                    m_pQuadRenderable->Render(glState);

                    glState.Blend.Enable();
                    glState.BlendFunc(GL_DST_COLOR, GL_SRC_ALPHA);
                    glState.BlendEquation(GL_FUNC_ADD);
                    glState.StencilFunc(GL_EQUAL, 2, 0xFF);

                    Eegeo::v4 fillColor = Eegeo::v4(0.2f, 0.2f, 0.2f, 1.0f);
                    m_pColorMaterial->SetColor(fillColor);
                    m_pQuadRenderable->Render(glState);
                }

                void PoiRingRenderable::SetSphereTransforms(const Eegeo::m44& transform, const Eegeo::m44& viewProjection)
                {
                    m_modelTransform = transform;
                    m_viewProjection = viewProjection;
                    Eegeo::m44 mvp;
                    Eegeo::m44::Mul(mvp, m_viewProjection, m_modelTransform);
                    m_pSphereRenderable->SetModelViewProjection(mvp);
                }

                void PoiRingRenderable::SetInnerSphereScale(const float scale)
                {
                    m_innerSphereScale = scale*2.0f; // Because it's actually Radius now.
                }
            }
        }
    }
}
