// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingView.h"
#include "RenderCamera.h"
#include "RenderQueue.h"
#include "PoiRingRenderable.h"
#include "RenderableFilters.h"
#include "BatchedSpriteRenderable.h"
#include "Colors.h"
#include "Bounds.h"
#include "ITexturePageLayout.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingView::PoiRingView(PoiRingRenderable& poiRingRenderable,
                                         Eegeo::Rendering::Renderables::BatchedSpriteRenderable& iconRenderable)
                    : m_poiRingRenderable(poiRingRenderable)
                    , m_iconRenderable(iconRenderable)
                    , m_shouldRenderRing(false)
                {

                }

                PoiRingView::~PoiRingView()
                {
                }

                void PoiRingView::SetRingTransforms(const Eegeo::m44& sphereMvp) const
                {
                    m_poiRingRenderable.SetSphereMvp(sphereMvp);
                }

                void PoiRingView::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
                {
                    if (m_shouldRenderRing)
                    {
                        renderQueue.EnqueueRenderable(m_poiRingRenderable);
                        renderQueue.EnqueueRenderable(m_iconRenderable);
                    }
                }

                void PoiRingView::SetInnerSphereScale(const float scale)
                {
                    m_poiRingRenderable.SetInnerSphereScale(scale);
                }

                void PoiRingView::SetShouldRenderRing(bool shouldRenderRing)
                {
                    m_shouldRenderRing = shouldRenderRing;
                }

                void PoiRingView::AddIconSprite(const Eegeo::Camera::RenderCamera &renderCamera, const Eegeo::dv3& position, float scale)
                {
                    m_iconRenderable.Reset();
                    m_iconRenderable.SetModelViewProjection(renderCamera.GetViewProjectionMatrix());

                    const float dimensionInMeters = scale;

                    m_iconRenderable.AddSprite(renderCamera,
                                               position,
                                               Eegeo::v2(0, 0),
                                               Eegeo::v2(1, 1),
                                               Eegeo::Rendering::Colors::WHITE,
                                               Eegeo::v2(dimensionInMeters, dimensionInMeters));

                }
            }
        }
    }
}
