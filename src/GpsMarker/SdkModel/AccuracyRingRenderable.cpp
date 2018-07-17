// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AccuracyRingRenderable.h"
#include "GLState.h"
#include "ColorMaterial.h"
#include "WorldMeshRenderable.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace
        {
            const int StencilClear = 2;
            const int StencilOuterLayer = 3;
            const int StencilInnerLayer = 4;
        }

        namespace SdkModel
        {
            AccuracyRingRenderable::AccuracyRingRenderable(
                    Eegeo::Rendering::Materials::ColorMaterial &colorMaterial,
                    Eegeo::Rendering::Materials::IMaterial& nullMaterial,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable &sphereRenderable,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable &quadRenderable)
            : Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::ScreenOverlay,
                                               Eegeo::dv3::Zero(),
                                               &nullMaterial)
            , m_innerRingRadius(100.f)
            , m_outerRingRadius(110.f)
            , m_ringColor(Eegeo::v4::One())
            , m_innerColor(0.7f, 0.7f, 0.7f, 0.5f)
            , m_colorMaterial(colorMaterial)
            , m_quadRenderable(quadRenderable)
            , m_sphereRenderable(sphereRenderable)
            {
            }

            AccuracyRingRenderable::~AccuracyRingRenderable()
            {
            }

            void AccuracyRingRenderable::Render(Eegeo::Rendering::GLState &glState) const
            {
                // NOTE: This isn't being rendered like a traditional WRLD Renderable.
                RenderClearStencil(glState);
                RenderSpheres(glState);
                RenderRingEffects(glState);
            }

            void AccuracyRingRenderable::RenderClearStencil(Eegeo::Rendering::GLState& glState) const
            {
                m_colorMaterial.SetState(glState);

                glState.DepthMask(GL_FALSE);
                glState.DepthTest.Enable();
                glState.DepthFunc(GL_ALWAYS);
                glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                glState.Blend.Disable();
                glState.StencilTest.Enable();
                glState.StencilFunc(GL_ALWAYS, StencilClear, 0xFF);
                glState.StencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

                m_quadRenderable.Render(glState);
            }

            void AccuracyRingRenderable::RenderSpheres(Eegeo::Rendering::GLState &glState) const
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

                Eegeo::m44 transform;
                Eegeo::m44 mvp;
                transform.Scale(m_outerRingRadius*2);
                transform.SetRow(3, Eegeo::v4(m_cameraRelativePosition, 1.0f));
                Eegeo::m44::Mul(mvp, m_viewProjection, transform);
                m_sphereRenderable.SetModelViewProjection(mvp);
                m_sphereRenderable.Render(glState);

                transform.Scale(m_innerRingRadius*2);
                transform.SetRow(3, Eegeo::v4(m_cameraRelativePosition, 1.0f));
                Eegeo::m44::Mul(mvp, m_viewProjection, transform);
                m_sphereRenderable.SetModelViewProjection(mvp);
                m_sphereRenderable.Render(glState);
            }

            void AccuracyRingRenderable::RenderRingEffects(Eegeo::Rendering::GLState &glState) const
            {
                m_colorMaterial.SetState(glState);

                Eegeo::v4 ringCol = m_ringColor;
                Eegeo::v4 innerCol = m_innerColor;

                m_colorMaterial.SetColor(ringCol);
                glState.ColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                glState.Blend.Enable();

                glState.StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                glState.ColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                glState.StencilFunc(GL_EQUAL, StencilOuterLayer, 0xFF);
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);

                m_quadRenderable.Render(glState);

                glState.Blend.Enable();
                glState.BlendFunc(GL_DST_COLOR, GL_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.StencilFunc(GL_EQUAL, StencilInnerLayer, 0xFF);

                m_colorMaterial.SetColor(innerCol);
                m_quadRenderable.Render(glState);
            }

            void AccuracyRingRenderable::SetTransforms(const Eegeo::v3 cameraRelativePosition,
                                                       const Eegeo::m44& viewProjection)
            {
                m_cameraRelativePosition = cameraRelativePosition;
                m_viewProjection = viewProjection;
            }

            void AccuracyRingRenderable::SetRadii(float outerRadius, float innerRadius)
            {
                m_innerRingRadius = innerRadius;
                m_outerRingRadius = outerRadius;
            }

            void AccuracyRingRenderable::SetColors(const Eegeo::v4& innerColor, const Eegeo::v4& ringColor)
            {
                m_innerColor = innerColor;
                m_ringColor = ringColor;
            }
        }
    }
}