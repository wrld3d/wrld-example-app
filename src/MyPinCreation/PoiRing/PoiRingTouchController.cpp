// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiRingTouchController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IMyPinCreationModel.h"
#include "GlobeCameraController.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            PoiRingTouchController::PoiRingTouchController(IMyPinCreationModel& myPinCreationModel,
                                                           Eegeo::Resources::Terrain::Collision::IRayPicker& rayPicker)
            : m_myPinCreationModel(myPinCreationModel)
            , m_rayPicker(rayPicker)
            , m_isDragging(false)
            {
                
            }
            
            bool PoiRingTouchController::HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
            {
                if (m_myPinCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                
                Eegeo::dv3 rayOrigin = globeCameraController.ComputeNonFlattenedCameraPosition();
                Eegeo::dv3 rayIntersectionPoint;
                double intersectionParam;
                bool rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                
                if (rayPick)
                {
                    const Eegeo::dv3& currentPosition = m_myPinCreationModel.GetPosition();
                    float cameraAltitude = rayOrigin.Length() - Eegeo::Space::EarthConstants::Radius;
                    const float touchRadius = 100.f + cameraAltitude/20;
                    
                    
                    if ((rayIntersectionPoint - currentPosition).Length() < touchRadius)
                    {
                        m_isDragging = true;
                        return true;
                    }
                }
                
                return false;
            }
            
            bool PoiRingTouchController::HandleTouchUp(const AppInterface::TouchData& data)
            {
                m_isDragging = false;
                
                if (m_myPinCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                return true;
            }
            
            bool PoiRingTouchController::HandleTouchMove(const AppInterface::TouchData &data, const Eegeo::Camera::RenderCamera &renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
            {
                if (m_myPinCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                if (m_isDragging)
                {
                    float screenPixelX = data.point.GetX();
                    float screenPixelY = data.point.GetY();
                    
                    Eegeo::dv3 rayDirection;
                    Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                    
                    Eegeo::dv3 rayOrigin = globeCameraController.ComputeNonFlattenedCameraPosition();
                    Eegeo::dv3 rayIntersectionPoint;
                    double intersectionParam;
                    bool rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                    
                    if (rayPick)
                    {
                        m_myPinCreationModel.SetPosition(rayIntersectionPoint);
                    }
                    
                    return true;
                }
                
                return false;
            }
            
            bool PoiRingTouchController::IsDragging() const
            {
                return m_isDragging && m_myPinCreationModel.GetCreationStage() == Ring;
            }
        }
    }
}