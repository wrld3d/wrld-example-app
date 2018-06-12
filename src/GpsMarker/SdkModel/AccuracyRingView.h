// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "Space.h"
#include "Rendering.h"
#include "GpsMarker.h"
#include "Camera.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class AccuracyRingView : public Eegeo::Rendering::IRenderableFilter {
            public:

                AccuracyRingView(AccuracyRingRenderable& renderable);
                ~AccuracyRingView();

                void SetPosition(const Eegeo::dv3& positionEcef);
                void SetAccuracyRange(float accuracyMeters);
                void SetEnabled(bool enabled);

                void Update(float dt,
                            const Eegeo::Camera::RenderCamera& renderCamera);

                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext,
                                        Eegeo::Rendering::RenderQueue& renderQueue);

            private:

                AccuracyRingRenderable& m_accuracyRingRenderable;

                Eegeo::dv3 m_positionEcef;
                float m_currentAccuracyMeters;
                float m_targetAccuracyMeters;
                bool m_enabled;

            };
        }
    }
}


