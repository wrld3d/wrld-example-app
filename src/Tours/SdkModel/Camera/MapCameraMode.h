// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraMode.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "GlobeCamera.h"
#include "EarthConstants.h"
#include "ToursCameraState.h"
#include "LatLongAltitude.h"
#include "MathFunc.h"
#include "Rendering.h"

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
                                  float distanceToInterest,
                                  float groundAltitude,
                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory);
                    
                    ~MapCameraMode();
                    
                    void Reset();
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale);
                    
                    const ToursCameraState& GetCurrentState() const;
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::dv3 m_mapCenterEcef;
                    Eegeo::Space::EcefTangentBasis m_tangentBasis;
                    
                    float m_groundAltitude;
                    
                    float m_mapExtentsX;
                    float m_mapExtentsZ;
                    
                    const float m_startingDistanceToInterest;
                    
                    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
                };
            }
        }
    }
}