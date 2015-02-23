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

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingRenderable::PoiRingRenderable(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                     Eegeo::Helpers::IFileIO& fileIO,
                                                     Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                                                     Eegeo::Lighting::GlobalFogging& globalFogging)
                    : Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::AfterAll,
                                                       Eegeo::dv3::Zero(),
                                                       &renderingModule.GetNullMaterial())
                    , m_fogging(globalFogging)
                    , m_innerSphereScale(165.f)
                {
                    m_pSphere = Eegeo::Model::CreateFromPODFile("Geosphere_01.pod", fileIO, &textureRequestor, "");

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

                }

                PoiRingRenderable::~PoiRingRenderable()
                {
                    Eegeo_DELETE m_pQuadRenderable;
                    Eegeo_DELETE m_pColorMaterial;
                    Eegeo_DELETE m_pColorShader;
                    Eegeo_DELETE m_pSphere;
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

                    m_pSphere->Draw(glState, m_fogging);

                    Eegeo::Node* pRoot = m_pSphere->GetRootNode();
                    const Eegeo::m44& originalLocalMatrix = pRoot->GetLocalMatrix();
                    const Eegeo::v4& originalCameraRelativePosition = originalLocalMatrix.GetRow(3);

                    Eegeo::m44 transform;
                    transform.Scale(m_innerSphereScale);
                    transform.SetRow(3, originalCameraRelativePosition);

                    SetSphereMvp(transform);
                    m_pSphere->Draw(glState, m_fogging);
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

                void PoiRingRenderable::SetSphereMvp(const Eegeo::m44& mvp) const
                {
                    Eegeo::Node* pRootNode = m_pSphere->GetRootNode();
                    pRootNode->SetLocalMatrix(mvp);
                    m_pSphere->Update();
                }

                void PoiRingRenderable::SetInnerSphereScale(const float scale)
                {
                    m_innerSphereScale = scale;
                }
            }
        }
    }
}
