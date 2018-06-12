// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RenderableBase.h"
#include "Rendering.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class AccuracyRingRenderable : public Eegeo::Rendering::RenderableBase
            {

            public:
                AccuracyRingRenderable(
                        Eegeo::Rendering::Materials::ColorMaterial& colorMaterial,
                        Eegeo::Rendering::Materials::IMaterial& nullMaterial,
                        Eegeo::Rendering::Renderables::WorldMeshRenderable& sphereRenderable,
                        Eegeo::Rendering::Renderables::WorldMeshRenderable& quadRenderable);

                ~AccuracyRingRenderable();

                void Render(Eegeo::Rendering::GLState& glState) const;

                void SetTransforms(const Eegeo::v3 cameraOffsetPosition, const Eegeo::m44& viewProj);
                void SetRadii(float outerRadius, float innerRadius);
                void SetColors(const Eegeo::v4& innerColor, const Eegeo::v4& ringColor);
            private:

                Eegeo::Rendering::Materials::ColorMaterial& m_colorMaterial;
                Eegeo::Rendering::Renderables::WorldMeshRenderable& m_quadRenderable;
                Eegeo::Rendering::Renderables::WorldMeshRenderable& m_sphereRenderable;

                Eegeo::m44 m_viewProjection;
                Eegeo::v3 m_cameraRelativePosition;
                Eegeo::v4 m_innerColor;
                Eegeo::v4 m_ringColor;
                float m_outerRingRadius;
                float m_innerRingRadius;

                void RenderClearStencil(Eegeo::Rendering::GLState& glState) const;
                void RenderSpheres(Eegeo::Rendering::GLState& glState) const;
                void RenderRingEffects(Eegeo::Rendering::GLState& glState) const;
            };
        }
    }

}

