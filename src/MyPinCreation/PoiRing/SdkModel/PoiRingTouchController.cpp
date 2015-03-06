// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingTouchController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IMyPinCreationModel.h"
#include "GlobeCameraController.h"
#include "EarthConstants.h"
#include "IntersectionTests.h"
#include "IPoiRingController.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingTouchController::PoiRingTouchController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                        Eegeo::Collision::IRayPicker& rayPicker,
                        const IPoiRingController& poiRingController)
                    : m_myPinCreationModel(myPinCreationModel)
                    , m_rayPicker(rayPicker)
                    , m_poiRingController(poiRingController)
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

                    bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);

                    if (rayPick)
                    {
                        const Eegeo::dv3& currentPosition = m_myPinCreationModel.GetPosition();
                        float cameraAltitude = static_cast<float>(rayOrigin.Length() - Eegeo::Space::EarthConstants::Radius);
                        const float touchRadius = 100.f + cameraAltitude/20;

                        Eegeo::dv3 iconPosition;
                        float iconSize;
                        m_poiRingController.GetIconPositionAndSize(iconPosition, iconSize);

                        bool hitIcon = Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, iconPosition, iconSize/2.0f);
                        if ((rayIntersectionPoint - currentPosition).Length() < touchRadius || hitIcon)
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
                        bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);

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

                bool PoiRingTouchController::PerformRayPick(Eegeo::dv3 &rayOrigin, Eegeo::dv3 &rayDirection, Eegeo::dv3 &out_rayIntersectionPoint, double &out_intersectionParam)
                {
                    bool rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, out_intersectionParam);
                    if(!rayPick)
                    {
                        rayPick = Eegeo::Geometry::IntersectionTests::GetRayEarthSphereIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, Eegeo::Space::EarthConstants::RadiusSquared);
                        if(rayPick)
                        {
                            out_intersectionParam = (out_rayIntersectionPoint - rayOrigin).Length();
                        }
                    }

                    return rayPick;
                }
            }
        }
    }
}
