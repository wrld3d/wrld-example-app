//
// Created by malcolm.brown on 08/06/2018.
//

#pragma once

#include "IRenderableFilter.h"
#include "Space.h"
#include "Rendering.h"
#include "GpsMarker.h"
#include "Interiors.h"
#include "Terrain.h"
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

                AccuracyRingView(AccuracyRingRenderable& renderable,
                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
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
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;

                Eegeo::dv3 m_positionEcef;
                float m_currentAccuracyMeters;
                float m_targetAccuracyMeters;
                bool m_enabled;

            };
        }
    }
}


