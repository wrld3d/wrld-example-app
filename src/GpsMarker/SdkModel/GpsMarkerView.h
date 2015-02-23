// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "Rendering.h"
#include "VectorMathDecl.h"
#include "Camera.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerView : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                
                GpsMarkerView(Eegeo::Rendering::Renderables::BatchedSpriteRenderable& iconRenderable);
                ~GpsMarkerView();
                
                void SetVisible(bool visible);
                void SetScale(float scaleParam);
                void Update(float dt);
                void DrawIconAtEcefPosition(const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& ecefPosition);
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                
            private:
                
                Eegeo::Rendering::Renderables::BatchedSpriteRenderable& m_iconRenderable;
                bool m_visible;
                float m_transitionParam;
                float m_scaleParam;
            };
        }
    }
}