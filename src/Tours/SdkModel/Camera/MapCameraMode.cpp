// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapCameraMode.h"
#include "GlobeCameraController.h"
#include "GlobeCameraControllerFactory.h"
#include "RenderCamera.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                MapCameraMode::MapCameraMode(const Eegeo::Space::LatLongAltitude& borderPositionTopLeft,
                                             const Eegeo::Space::LatLongAltitude& borderPositionBottomRight,
                                             float distanceToInterest,
                                             float groundAltitude,
                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory)
                : m_startingDistanceToInterest(distanceToInterest)
                , m_groundAltitude(groundAltitude)
                , m_pCameraController(NULL)
                {
                    Eegeo::dv3 topLeft = borderPositionTopLeft.ToECEF();
                    Eegeo::dv3 bottomRight = borderPositionBottomRight.ToECEF();
                    m_mapCenterEcef = (bottomRight + topLeft)*0.5;
                    m_mapCenterEcef = m_mapCenterEcef.Norm() * (Eegeo::Space::EarthConstants::Radius + groundAltitude);
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_mapCenterEcef, 0, m_tangentBasis);
                    
                    m_mapExtentsX = Eegeo::Math::Abs(Eegeo::v3::Dot((topLeft - m_mapCenterEcef).ToSingle(), m_tangentBasis.GetRight()));
                    m_mapExtentsZ = Eegeo::Math::Abs(Eegeo::v3::Dot((bottomRight - m_mapCenterEcef).ToSingle(), m_tangentBasis.GetForward()));
                    
                    Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(false);
                    
                    globeCameraConfig.terrainFollowingEnabled = false;
                    globeCameraConfig.zoomAltitudeLow = 10.0f;
                    globeCameraConfig.fovZoomedInCity = 45.0f;
                    globeCameraConfig.fovZoomedInGlobe = 90.0f;
                    globeCameraConfig.maxAltitude = 120.0f;
                    globeCameraConfig.computeNearFarPlanes = false;
                    globeCameraConfig.nearPlane = 1.f;
                    globeCameraConfig.farPlane = 5000.f;
                    
                    m_pCameraController = cameraControllerFactory.CreateCameraController(globeCameraConfig, touchController, screenProperties);
                }
                
                MapCameraMode::~MapCameraMode()
                {
                    Eegeo_DELETE m_pCameraController;
                    m_pCameraController = NULL;
                }
                
                void MapCameraMode::Reset()
                {
                    Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_mapCenterEcef, 0.0f, cameraInterestBasis);
                    
                    m_pCameraController->SetView(cameraInterestBasis, m_startingDistanceToInterest);
                }
                
                void MapCameraMode::UpdateCamera(float dt,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                 float inputScreenScale)
                {
                    m_pCameraController->Update(dt);
                    
                    Eegeo::dv3 cameraInterestEcef = m_pCameraController->GetInterestBasis().GetPointEcef();
                    cameraInterestEcef = cameraInterestEcef.Norm() * (Eegeo::Space::EarthConstants::Radius + m_groundAltitude);
                    
                    Eegeo::v3 relativeCameraInterestEcef = (cameraInterestEcef - m_mapCenterEcef).ToSingle();
                    
                    Eegeo::v3 cameraInterestTangentSpace = Eegeo::v3(Eegeo::v3::Dot(relativeCameraInterestEcef, m_tangentBasis.GetRight()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, m_tangentBasis.GetUp()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, m_tangentBasis.GetForward()));
                    
                    cameraInterestTangentSpace.Set(cameraInterestTangentSpace.x, m_groundAltitude, cameraInterestTangentSpace.z);
                    
                    if(cameraInterestTangentSpace.x < -m_mapExtentsX ||
                       cameraInterestTangentSpace.x > m_mapExtentsX ||
                       cameraInterestTangentSpace.z < -m_mapExtentsZ ||
                       cameraInterestTangentSpace.z > m_mapExtentsZ)
                    {
                        float newX = Eegeo::Math::Clamp(cameraInterestTangentSpace.x, -m_mapExtentsX, m_mapExtentsX);
                        float newZ = Eegeo::Math::Clamp(cameraInterestTangentSpace.z, -m_mapExtentsZ, m_mapExtentsZ);
                        cameraInterestTangentSpace.Set(newX, m_groundAltitude, newZ);
                    }
                    
                    
                    Eegeo::m33 tangentBasis;
                    m_tangentBasis.GetBasisOrientationAsMatrix(tangentBasis);
                    relativeCameraInterestEcef = Eegeo::v3::Mul(cameraInterestTangentSpace, tangentBasis);
                    
                    Eegeo::Space::EcefTangentBasis cameraInterestBasis = m_pCameraController->GetInterestBasis();
                    cameraInterestBasis.SetPoint(m_mapCenterEcef + relativeCameraInterestEcef);
                    m_pCameraController->SetInterestBasis(cameraInterestBasis);
                    
                    m_cameraState.ecefInterestPoint = m_pCameraController->GetEcefInterestPoint();
                    m_cameraState.ecefPosition = m_pCameraController->GetRenderCamera().GetEcefLocation();
                    m_cameraState.orientationMatrix = m_pCameraController->GetRenderCamera().GetModelMatrix();
                    m_cameraState.fovDegrees = Eegeo::Math::Rad2Deg(m_pCameraController->GetRenderCamera().GetFOV());
                }
                
                
                const ToursCameraState& MapCameraMode::GetCurrentState() const
                {
                    return m_cameraState;
                }
                
            }
        }
    }
}
