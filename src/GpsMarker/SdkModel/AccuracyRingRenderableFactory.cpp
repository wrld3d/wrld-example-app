// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AccuracyRingRenderableFactory.h"
#include "LayerIds.h"
#include "NullMaterial.h"
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
#include "PositionMeshFactory.h"
#include "AccuracyRingRenderable.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            AccuracyRingRenderableFactory* AccuracyRingRenderableFactory::Create(Eegeo::Modules::Core::RenderingModule& renderingModule)
            {
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                Eegeo::Rendering::Shaders::ColorShader *pColorShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());

                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                Eegeo::Rendering::Materials::ColorMaterial* pColorMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::ColorMaterial)(materialIdGenerator.GetNextId(),
                                                                                         "RingQuadStencilMat",
                                                                                         *pColorShader,
                                                                                         Eegeo::v4::One());

                Eegeo::Rendering::Mesh* pQuadMesh = Eegeo::Rendering::Geometry::CreatePositionQuad(renderingModule.GetGlBufferPool(),
                                                                                                   renderingModule.GetVertexLayoutPool());

                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = renderingModule.GetVertexBindingPool();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& quadVertexBinding = vertexBindingPool.GetVertexBinding(pQuadMesh->GetVertexLayout(),
                                                                                                                             pColorShader->GetVertexAttributes());

                Eegeo::Rendering::Renderables::WorldMeshRenderable* pQuadRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                                                                                  pColorMaterial,
                                                                                                  quadVertexBinding,
                                                                                                  pQuadMesh,
                                                                                                  Eegeo::dv3::Zero());
                pQuadRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

                std::vector<Eegeo::v3> sphereVerts;
                std::vector<u16> sphereIndices;
                const int tesselation = 8;
                Eegeo::Rendering::Geometry::BuildUnitSphere(sphereVerts, sphereIndices, tesselation);

                Eegeo::Rendering::MeshFactories::PositionMeshFactory& meshFactory = renderingModule.GetPositionMeshFactory();
                Eegeo::Rendering::Mesh* pSphereMesh = meshFactory.CreateMesh(sphereVerts, sphereIndices, "sphere");

                const Eegeo::Rendering::VertexLayouts::VertexBinding& sphereVertexBinding = vertexBindingPool.GetVertexBinding(pSphereMesh->GetVertexLayout(),
                                                                                                                               pColorShader->GetVertexAttributes());
                Eegeo::Rendering::Renderables::WorldMeshRenderable* pSphereRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                                                                                    pColorMaterial,
                                                                                                    sphereVertexBinding,
                                                                                                    pSphereMesh,
                                                                                                    Eegeo::dv3::Zero());
                pSphereRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

                return Eegeo_NEW(AccuracyRingRenderableFactory)(
                        pColorShader,
                        pColorMaterial,
                        pSphereRenderable,
                        pQuadRenderable,
                        renderingModule.GetNullMaterial());
            }

            AccuracyRingRenderableFactory::AccuracyRingRenderableFactory(
                    Eegeo::Rendering::Shaders::ColorShader *pColorShader,
                    Eegeo::Rendering::Materials::ColorMaterial *pColorMaterial,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable *pSphereRenderable,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable *pQuadRenderable,
                    Eegeo::Rendering::Materials::IMaterial& nullMaterial)
            : m_pColorShader(pColorShader)
            , m_pColorMaterial(pColorMaterial)
            , m_pSphereRenderable(pSphereRenderable)
            , m_pQuadRenderable(pQuadRenderable)
            , m_nullMaterial(nullMaterial)
            {

            }

            AccuracyRingRenderableFactory::~AccuracyRingRenderableFactory()
            {
                Eegeo_DELETE m_pQuadRenderable;
                Eegeo_DELETE m_pSphereRenderable;
                Eegeo_DELETE m_pColorMaterial;
                Eegeo_DELETE m_pColorShader;
            }

            AccuracyRingRenderable* AccuracyRingRenderableFactory::BuildRenderable()
            {
                auto* pRenderable = Eegeo_NEW(AccuracyRingRenderable)(
                        *m_pColorMaterial,
                        m_nullMaterial,
                        *m_pSphereRenderable,
                        *m_pQuadRenderable);
                pRenderable->SetLayer(Eegeo::Rendering::LayerIds::ScreenOverlay);
                pRenderable->SetUserDefined(1);
                return pRenderable;
            }
        }
    }
}