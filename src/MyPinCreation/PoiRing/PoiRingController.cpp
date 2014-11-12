// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiRingController.h"
#include "TtyHandler.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IRayPicker.h"
#include "PoiRingView.h"
#include "RenderContext.h"
#include "ScreenProperties.h"
#include "MathFunc.h"
#include "MathsHelpers.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationModel.h"

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
                                                 const Eegeo::Rendering::ScreenProperties& screenProperties)
            : m_pMyPinCreationModel(myPinCreationModel)
            , m_poiRingView(poiRingView)
            , m_screenProperties(screenProperties)
            , m_scaleInterpolationParam(0.f)
            , m_easeDurationInSeconds(1.2f)
            {
                
            }
            
            void PoiRingController::Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint)
            {
                m_poiRingView.SetShouldRenderRing(m_scaleInterpolationParam > 0.f);
                
                if (m_pMyPinCreationModel.GetCreationStage() == Inactive && m_scaleInterpolationParam < 0.01f)
                {
                    m_pMyPinCreationModel.SetPosition(cameraEcefInterestPoint);
                }
                
                // TODO, quad should scale up and down. May also need to lerp position.
                Eegeo::v3 quadTranslation = CalculateQuadScreenSpaceTranslation(renderCamera);
                Eegeo::m44 quadTransformMatrix;
                quadTransformMatrix.Scale(0.7f);
                quadTransformMatrix.SetRow(3, Eegeo::v4(quadTranslation, 1.f));
            
                Eegeo::m44 sphereTransformMatrix;
                
                const float transitionScale = CalculateTransitionScale(dt);
                const float outerRingRadiusInMeters = 120.f;
                sphereTransformMatrix.Scale(outerRingRadiusInMeters * transitionScale);
                
                Eegeo::dv3 cameraRelativePosition = m_pMyPinCreationModel.GetPosition() - renderCamera.GetEcefLocation();
                sphereTransformMatrix.SetRow(3, Eegeo::v4(cameraRelativePosition.ToSingle(), 1.f));
                
                m_poiRingView.SetRingTransforms(sphereTransformMatrix, quadTransformMatrix);
                
                float altitudeBasedScale = CalculateAltitudeBasedSphereScale(renderCamera.GetAltitude(), outerRingRadiusInMeters);
                m_poiRingView.SetInnerSphereScale(altitudeBasedScale * transitionScale);
                
                Eegeo::v3 up = m_pMyPinCreationModel.GetPosition().Norm().ToSingle();
                const float iconHeightInMeters = 150.f * transitionScale;
                Eegeo::dv3 iconPosition = m_pMyPinCreationModel.GetPosition() + (up * iconHeightInMeters);
                const float iconScale = CalculateAltitudeBasedIconScale(renderCamera.GetAltitude());
                m_poiRingView.AddIconSprite(renderCamera, iconPosition, iconScale * transitionScale);
            }
            
            Eegeo::v3 PoiRingController::CalculateQuadScreenSpaceTranslation(const Eegeo::Camera::RenderCamera& renderCamera) const
            {
                Eegeo::v3 projectedQuadPosition;
                
                Eegeo::dv3 cameraRelativePosition = m_pMyPinCreationModel.GetPosition() - renderCamera.GetEcefLocation();
                renderCamera.Project(cameraRelativePosition.ToSingle(), projectedQuadPosition);
                
                float normalisedX = projectedQuadPosition.GetX() / m_screenProperties.GetScreenWidth();
                float normalisedY = projectedQuadPosition.GetY() / m_screenProperties.GetScreenHeight();
                
                float screenBoundsMin = 0.f;
                float screenBoundsMax = 1.f;
                float quadBoundsMin = -1.f;
                float quadBoundsMax = 1.f;
                
                float xPosition = (((normalisedX - screenBoundsMin) * (quadBoundsMax - quadBoundsMin)) / (screenBoundsMax - screenBoundsMin)) + quadBoundsMin;
                float yPosition = (((normalisedY - screenBoundsMin) * (quadBoundsMax - quadBoundsMin)) / (screenBoundsMax - screenBoundsMin)) + quadBoundsMin;
                
                Eegeo::v3 transformPosition;
                transformPosition.Set(xPosition, -yPosition, 0.f);
                
                return transformPosition;
            }
            
            float PoiRingController::CalculateTransitionScale(float dt)
            {
                float delta = m_pMyPinCreationModel.GetCreationStage() == Ring ? dt : -dt;
                delta /= m_easeDurationInSeconds;
                m_scaleInterpolationParam = Eegeo::Clamp(m_scaleInterpolationParam + delta, 0.f, 1.f);
                return Eegeo::Helpers::MathsHelpers::PennerElasticEaseInOut(0.f, 1.f, m_scaleInterpolationParam);
            }
        }
    }
}