// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerView.h"
#include "RenderQueue.h"
#include "BatchedSpriteRenderable.h"
#include "Colors.h"
#include "VectorMath.h"
#include "RenderCamera.h"
#include "TransformHelpers.h"
#include "GpsMarkerViewFactory.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerView::GpsMarkerView(const std::shared_ptr<GpsMarkerViewFactory>& factory)
            : m_iconRenderable(factory->GetRenderable())
            , m_transitionParam(1.0f)
            , m_scaleParam(1.0f)
            , m_visible(true)
            {
                
            }
            
            GpsMarkerView::~GpsMarkerView()
            {
                
            }
            
            void GpsMarkerView::SetVisible(bool visible)
            {
                m_visible = visible;
            }
            
            void GpsMarkerView::SetScale(float scaleParam)
            {
                m_scaleParam = Eegeo::Math::Clamp01(scaleParam);
            }
            
            void GpsMarkerView::Update(float dt)
            {
                if(m_visible && m_transitionParam < 1.0f)
                {
                    m_transitionParam += dt * 4.0f;
                }
                else if(!m_visible && m_transitionParam > 0.0f)
                {
                    m_transitionParam -= dt * 4.0f;
                }
                m_transitionParam = Eegeo::Math::Clamp01(m_transitionParam);
                
                m_iconRenderable.Reset();
            }
            
            void GpsMarkerView::DrawIconAtEcefPosition(const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& ecefPosition)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                m_iconRenderable.SetModelViewProjection(renderCamera.GetViewProjectionMatrix());
                
                const float iconConstantScale = 0.3f;
                const float iconScale = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(renderCamera, ecefPosition) * iconConstantScale * m_transitionParam * m_scaleParam;
                
                m_iconRenderable.AddSprite(renderCamera,
                                           ecefPosition,
                                           Eegeo::v2(0, 0),
                                           Eegeo::v2(1, 1),
                                           Eegeo::Rendering::Colors::WHITE,
                                           Eegeo::v2(iconScale, iconScale));
            }
            
            void GpsMarkerView::EnqueueRenderables(const Eegeo::Rendering::RenderContext &renderContext, Eegeo::Rendering::RenderQueue &renderQueue)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                renderQueue.EnqueueRenderable(m_iconRenderable);
            }
        }
    }
}