// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiRingController.h"
#include "TtyHandler.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IRayPicker.h"
#include "PoiRingView.h"
#include "RenderContext.h"
#include "MathFunc.h"
#include "MathsHelpers.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationModel.h"
#include "EarthConstants.h"
#include "TerrainHeightProvider.h"
#include "TransformHelpers.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace
            {
                float CalculateAltitudeBasedSphereScale(float altitude, float outerRingRadiusInMeters)
                {
                    const float minAltitude = 500.f;
                    const float maxAltitude = 18000.f;
                    const float lowAltitudeSphereScale = outerRingRadiusInMeters - 2.f;
                    const float highAltitudeSphereScale = outerRingRadiusInMeters - 100.f;
                    return lowAltitudeSphereScale + (((altitude - minAltitude)/maxAltitude) * (highAltitudeSphereScale - lowAltitudeSphereScale));
                }
                
                float CalculateAltitudeBasedIconScale(float altitude)
                {
                    const float minAltitude = 500.f;
                    const float maxAltitude = 18000.f;
                    const float lowAltitudeIconScale = 1.f;
                    const float highAltitudeIconScale = 10.f;
                    return lowAltitudeIconScale + (((altitude - minAltitude)/maxAltitude) * (highAltitudeIconScale - lowAltitudeIconScale));
                }
            }
            
            PoiRingController::PoiRingController(IMyPinCreationModel& myPinCreationModel,
                                                 PoiRingView& poiRingView,
                                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                 Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
            : m_pMyPinCreationModel(myPinCreationModel)
            , m_poiRingView(poiRingView)
            , m_scaleInterpolationParam(0.f)
            , m_easeDurationInSeconds(1.2f)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_iconPosition(Eegeo::dv3::Zero())
            , m_iconSize(0.0f)
            {
                
            }
            
            void PoiRingController::Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint)
            {
                m_poiRingView.SetShouldRenderRing(m_scaleInterpolationParam > 0.f);
                
                if (m_pMyPinCreationModel.GetCreationStage() == Inactive && m_scaleInterpolationParam < 0.01f)
                {
                    m_pMyPinCreationModel.SetPosition(cameraEcefInterestPoint);
                }
                
                if(m_pMyPinCreationModel.NeedsTerrainHeight())
                {
                    float terrainHeight;
                    if(m_terrainHeightProvider.TryGetHeight(m_pMyPinCreationModel.GetPosition(), 11, terrainHeight))
                    {
                        m_pMyPinCreationModel.SetTerrainHeight(terrainHeight);
                    }
                }
            
                Eegeo::m44 sphereTransformMatrix;
                
                const float transitionScale = CalculateTransitionScale(dt);
                const float outerRingRadiusInMeters = 120.f;
                sphereTransformMatrix.Scale(outerRingRadiusInMeters * transitionScale);
                
                Eegeo::dv3 scaledPoint = Eegeo::Rendering::EnvironmentFlatteningService::GetScaledPointEcef(m_pMyPinCreationModel.GetPosition(), m_environmentFlatteningService.GetCurrentScale());
                
                Eegeo::dv3 cameraRelativePosition = scaledPoint - renderCamera.GetEcefLocation();
                sphereTransformMatrix.SetRow(3, Eegeo::v4(cameraRelativePosition.ToSingle(), 1.f));
                
                m_poiRingView.SetRingTransforms(sphereTransformMatrix);
                
                float altitudeBasedScale = CalculateAltitudeBasedSphereScale(renderCamera.GetAltitude(), outerRingRadiusInMeters);
                m_poiRingView.SetInnerSphereScale(altitudeBasedScale * transitionScale);
                
                Eegeo::dv3 unflattenedIconPosition = m_pMyPinCreationModel.GetPosition();
                Eegeo::dv3 iconPosition = Eegeo::Rendering::EnvironmentFlatteningService::GetScaledPointEcef(
                    unflattenedIconPosition,
                    m_environmentFlatteningService.GetCurrentScale());

                const float iconConstantScale = 0.14f;
                const float iconScale = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(renderCamera, iconPosition) * iconConstantScale;
                m_iconSize = Eegeo::Max(iconScale * transitionScale, 0.0f);
                m_poiRingView.AddIconSprite(renderCamera, iconPosition, m_iconSize);
                
                m_iconPosition = iconPosition + (Eegeo::dv3)renderCamera.GetModelMatrix().GetRow(1) * m_iconSize * 0.5f;
            }
            
            float PoiRingController::CalculateTransitionScale(float dt)
            {
                float delta = m_pMyPinCreationModel.GetCreationStage() == Ring ? dt : -dt;
                delta /= m_easeDurationInSeconds;
                m_scaleInterpolationParam = Eegeo::Clamp(m_scaleInterpolationParam + delta, 0.f, 1.f);
                return Eegeo::Helpers::MathsHelpers::PennerElasticEaseInOut(0.f, 1.f, m_scaleInterpolationParam);
            }
            
            void PoiRingController::GetIconPositionAndSize(Eegeo::dv3& out_positionEcef, float& out_sizeMeters) const
            {
                out_positionEcef = m_iconPosition;
                out_sizeMeters = m_iconSize;
            }
        }
    }
}