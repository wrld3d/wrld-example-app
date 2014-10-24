// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiRingTouchController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IPoiCreationModel.h"
#include "IPoiCreationModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        namespace PoiRing
        {
            PoiRingTouchController::PoiRingTouchController(IPoiCreationModel& poiCreationModel,
                                                           Eegeo::Resources::Terrain::Collision::IRayPicker& rayPicker)
            : m_poiCreationModel(poiCreationModel)
            , m_rayPicker(rayPicker)
            , m_isDragging(false)
            {
                
            }
            
            bool PoiRingTouchController::HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera)
            {
                if (m_poiCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                
                Eegeo::dv3 rayIntersectionPoint;
                double intersectionParam;
                bool rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                
                if (rayPick)
                {
                    const Eegeo::dv3& currentPosition = m_poiCreationModel.GetPosition();
                    const float touchRadius = 170.f;
                    
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
                if (m_poiCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                m_isDragging = false;
                return true;
            }
            
            bool PoiRingTouchController::HandleTouchMove(const AppInterface::TouchData &data, const Eegeo::Camera::RenderCamera &renderCamera)
            {
                if (m_poiCreationModel.GetCreationStage() != Ring)
                {
                    return false;
                }
                
                if (m_isDragging)
                {
                    float screenPixelX = data.point.GetX();
                    float screenPixelY = data.point.GetY();
                    
                    Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                    Eegeo::dv3 rayDirection;
                    Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                    
                    Eegeo::dv3 rayIntersectionPoint;
                    double intersectionParam;
                    bool rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                    
                    if (rayPick)
                    {
                        m_poiCreationModel.SetPosition(rayIntersectionPoint);
                    }
                    
                    return true;
                }
                
                return false;
            }
            
            bool PoiRingTouchController::IsDragging() const
            {
                return m_isDragging;
            }
        }
    }
}