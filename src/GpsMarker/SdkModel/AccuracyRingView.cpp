//
// Created by malcolm.brown on 08/06/2018.
//

#include "AccuracyRingView.h"
#include "RenderCamera.h"
#include "AccuracyRingRenderable.h"
#include "RenderQueue.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "TerrainHeightProvider.h"
#include "MathsHelpers.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            namespace
            {
                float CalculateAltitudeBasedRingWidth(float altitude)
                {
                    const float minAltitude = 20.f;
                    const float maxAltitude = 1000.f;
                    const float lowAltitudeRadius = 0.1f;
                    const float highAltitudeRadius = 5.0f;
                    float t = Eegeo::Math::Clamp01((altitude - minAltitude)/(maxAltitude-minAltitude));
                    return Eegeo::Math::Lerp(lowAltitudeRadius, highAltitudeRadius, t);
                }
            }

            AccuracyRingView::AccuracyRingView(AccuracyRingRenderable & renderable,
                    Eegeo::Resources::Interiors::InteriorInteractionModel &interiorInteractionModel,
                    Eegeo::Rendering::EnvironmentFlatteningService & environmentFlatteningService,
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider &terrainHeightProvider
            )
            : m_accuracyRingRenderable(renderable)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_enabled(false)
            , m_currentAccuracyMeters(0.0f)
            , m_targetAccuracyMeters(0.0f)
            , m_positionEcef(Eegeo::dv3::Zero())
            {

            }

            AccuracyRingView::~AccuracyRingView()
            {

            }

            void AccuracyRingView::SetPosition(const Eegeo::dv3& positionEcef)
            {
                m_positionEcef = positionEcef;
            }

            void AccuracyRingView::SetAccuracyRange(float accuracyMeters)
            {
                m_targetAccuracyMeters = accuracyMeters;
            }

            void AccuracyRingView::SetEnabled(bool enabled)
            {
                m_enabled = enabled;
            }

            void AccuracyRingView::Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera)
            {
                if(!m_enabled)
                {
                    m_targetAccuracyMeters = 0.0f;
                }

                m_currentAccuracyMeters = Eegeo::Helpers::MathsHelpers::ExpMoveTowards(m_currentAccuracyMeters, m_targetAccuracyMeters, 0.1f, dt, 0.01f);

                if(m_currentAccuracyMeters <= 0.0f)
                {
                    return;
                }

                const float altitude = (float)(renderCamera.GetAltitude() - (m_positionEcef.Length() - Eegeo::Space::EarthConstants::Radius));
                const float ringWidth = CalculateAltitudeBasedRingWidth(altitude);
                m_accuracyRingRenderable.SetRadii(m_currentAccuracyMeters + ringWidth, m_currentAccuracyMeters);

                Eegeo::dv3 ecefPosition = m_positionEcef;

                Eegeo::v3 cameraOffset = (ecefPosition - renderCamera.GetEcefLocation()).ToSingle();
                m_accuracyRingRenderable.SetTransforms(cameraOffset, renderCamera.GetViewProjectionMatrix());
            }


            void AccuracyRingView::EnqueueRenderables(
                    const Eegeo::Rendering::RenderContext &renderContext,
                    Eegeo::Rendering::RenderQueue &renderQueue)
            {
                if(m_currentAccuracyMeters > 0.0f)
                {
                    renderQueue.EnqueueRenderable(m_accuracyRingRenderable);
                }
            }
        }
    }
}