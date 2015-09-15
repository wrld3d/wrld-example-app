// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraMode.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "GlobeCameraTouchController.h"
#include "EarthConstants.h"
#include "ToursCameraState.h"
#include "LatLongAltitude.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class MapCameraMode : public IToursCameraMode
                {
                public:
                    
                    MapCameraMode(const Eegeo::Space::LatLongAltitude& borderPositionTopLeft,
                                  const Eegeo::Space::LatLongAltitude& borderPositionBottomRight,
                                  float cameraAltitude)
                    : m_cameraAltitude(cameraAltitude)
                    , m_localFocusPoint(Eegeo::v2::Zero())
                    {
                        Eegeo::dv3 topLeft = borderPositionTopLeft.ToECEF();
                        Eegeo::dv3 bottomRight = borderPositionBottomRight.ToECEF();
                        m_mapCenterEcef = (bottomRight + topLeft)*0.5;
                        m_mapCenterEcef = m_mapCenterEcef.Norm() * Eegeo::Space::EarthConstants::Radius;
                        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_mapCenterEcef, 0, m_tangentBasis);
                        
                        m_mapExtentsX = Eegeo::Math::Abs(Eegeo::v3::Dot((bottomRight - m_mapCenterEcef).ToSingle(), m_tangentBasis.GetRight()));
                        m_mapExtentsY = Eegeo::Math::Abs(Eegeo::v3::Dot((bottomRight - m_mapCenterEcef).ToSingle(), m_tangentBasis.GetForward()));
                    }
                    
                    void Reset()
                    {
                        m_localFocusPoint = Eegeo::v2::Zero();
                    }
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale)
                    {
                        Eegeo::v2 delta = touchController.GetPanPixelDelta() * inputScreenScale * 1000.0f;
                        m_localFocusPoint += Eegeo::v2(-delta.x, delta.y);
                        
                        m_localFocusPoint.x = Eegeo::Math::Clamp(m_localFocusPoint.x, -m_mapExtentsX, m_mapExtentsX);
                        m_localFocusPoint.y = Eegeo::Math::Clamp(m_localFocusPoint.y, -m_mapExtentsY, m_mapExtentsY);
                        
                        Eegeo::v3 ecefOffset =  (m_tangentBasis.GetRight() * m_localFocusPoint.x) +
                                                (m_tangentBasis.GetForward() * m_localFocusPoint.y);
                        
                        
                        m_cameraState.ecefInterestPoint = m_mapCenterEcef + ecefOffset;
                        const float NorthOffset = -100.0f;
                        m_cameraState.ecefPosition = m_cameraState.ecefInterestPoint + m_cameraAltitude * m_tangentBasis.GetUp() + (NorthOffset * m_tangentBasis.GetForward());
                        
                        Eegeo::v3 up = m_tangentBasis.GetForward();
                        Eegeo::v3 at = (m_cameraState.ecefInterestPoint - m_cameraState.ecefPosition).Norm().ToSingle();
                        Eegeo::v3 right = m_tangentBasis.GetRight();
                        up = Eegeo::v3::Cross(at, right).Norm();
                        m_cameraState.orientationMatrix.SetFromBasis(right, up, at);
  
                        m_cameraState.fovDegrees = 40.0f;
                    }
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::dv3 m_mapCenterEcef;
                    Eegeo::Space::EcefTangentBasis m_tangentBasis;
                    
                    Eegeo::v2 m_localFocusPoint;
                    float m_cameraAltitude;
                    
                    float m_mapExtentsX;
                    float m_mapExtentsY;
                };
            }
        }
    }
}