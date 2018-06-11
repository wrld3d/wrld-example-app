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

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
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
                if(!m_enabled)
                {
                    m_targetAccuracyMeters = 0.0f;
                }
            }

            void AccuracyRingView::Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera)
            {
                m_currentAccuracyMeters = Eegeo::Helpers::MathsHelpers::ExpMoveTowards(m_currentAccuracyMeters, m_targetAccuracyMeters, 0.1f, dt, 0.01f);

                if(m_currentAccuracyMeters <= 0.0f)
                {
                    return;
                }

                const float ringWidth = .5f; // Should change with altitude?
                m_accuracyRingRenderable.SetRadii(m_currentAccuracyMeters + ringWidth, m_currentAccuracyMeters);

                Eegeo::dv3 ecefPosition = m_positionEcef;
                /*if(m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = m_interiorInteractionModel.GetInteriorModel();

                    ecefPosition += pModel->GetFloorAltitude(m_interiorInteractionModel.GetSelectedFloorIndex()) * ecefPosition.Norm();
                }
                else
                {
                    float height;
                    if(m_terrainHeightProvider.TryGetHeight(ecefPosition, 11, height))
                    {
                        ecefPosition += height * ecefPosition.Norm();
                    }
                }*/

                Eegeo::v3 cameraOffset = (ecefPosition - renderCamera.GetEcefLocation()).ToSingle();
                m_accuracyRingRenderable.SetTransforms(cameraOffset, renderCamera.GetViewProjectionMatrix());
            }


            void AccuracyRingView::EnqueueRenderables(
                    const Eegeo::Rendering::RenderContext &renderContext,
                    Eegeo::Rendering::RenderQueue &renderQueue)
            {
                //if(m_enabled && m_currentAccuracyMeters > 0.0f)
                {
                    renderQueue.EnqueueRenderable(m_accuracyRingRenderable);
                }
            }
        }
    }
}