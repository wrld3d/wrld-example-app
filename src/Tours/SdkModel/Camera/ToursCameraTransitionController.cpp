// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ToursCameraTransitionController.h"
#include "IToursCameraController.h"
#include "IToursCameraMode.h"
#include "IToursCameraTransitionMode.h"
#include "ITourService.h"
#include "ToursCameraFadeTransitionMode.h"
#include "GpsGlobeCameraController.h"
#include "TerrainHeightProvider.h"
#include "EarthConstants.h"
#include "IntersectionTests.h"
#include "InteriorsController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                ToursCameraTransitionController::ToursCameraTransitionController(IToursCameraController& toursCameraController,
                                                                                 Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                                                                 Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                                                                 Eegeo::Resources::Interiors::InteriorsController& interiorsController)
                : m_toursCameraController(toursCameraController)
                , m_pToursTransitionMode(NULL)
                , m_pToursCurrentMode(NULL)
                , m_pToursNextMode(NULL)
                , m_gpsGlobeCameraController(gpsGlobeCameraController)
                , m_terrainHeightProvider(terrainHeightProvider)
                , m_interiorsController(interiorsController)
                {
                    
                }
                
                ToursCameraTransitionController::~ToursCameraTransitionController()
                {
                    Eegeo_DELETE m_pToursTransitionMode;
                }
                
                bool ToursCameraTransitionController::IsTransitionComplete() const
                {
                    return m_pToursTransitionMode == NULL;
                }
                
                bool ToursCameraTransitionController::IsTransitioning() const
                {
                    return !IsTransitionComplete();
                }
                
                void ToursCameraTransitionController::SetAppCameraState(ToursCameraState& cameraState)
                {
                    m_appCameraState = cameraState;
                }
                
                void ToursCameraTransitionController::Update(float dt)
                {
                    if(m_pToursTransitionMode != NULL && m_pToursTransitionMode->HasEnded())
                    {
                        Eegeo_DELETE m_pToursTransitionMode;
                        m_pToursTransitionMode = NULL;
                        
                        m_pToursCurrentMode = NULL;
                        m_pToursCurrentMode = m_pToursNextMode;
                        m_toursCameraController.SetMode(m_pToursCurrentMode);
                    }
                }
                
                void ToursCameraTransitionController::TransitionTo(IToursCameraMode& targetCameraMode)
                {
                    IToursCameraMode* pTargetCameraMode(&targetCameraMode);
                    
                    m_pToursNextMode = pTargetCameraMode;
                    
                    // HACK - Need to ensure both modes have a valid state (by updating). Should ensure they're initialised as such.
                    m_pToursNextMode->UpdateCamera(0.0f, m_toursCameraController.GetTouchController(), 0.0f);
                                        
                    if(IsTransitioning()) // interrupting an in-flight transition
                    {
                        ToursCameraState currentTransitionCameraState(m_pToursTransitionMode->GetCurrentState());
                        Eegeo_DELETE m_pToursTransitionMode;
                        m_pToursTransitionMode = SplineTransitionCameraMode::CreateBetweenStates(currentTransitionCameraState,
                                                                                                 m_pToursNextMode->GetCurrentState());
                    }
                    else if(m_pToursCurrentMode != NULL) // transition from stable state
                    {
                        m_pToursTransitionMode = SplineTransitionCameraMode::CreateBetweenStates(m_pToursCurrentMode->GetCurrentState(),
                                                                                                 m_pToursNextMode->GetCurrentState());
                    }
                    else // 'transition' from app
                    {
                        PerformCameraTransitionOrFade(m_appCameraState,
                                                      m_pToursNextMode->GetCurrentState());
                    }
                    
                    m_toursCameraController.SetMode(m_pToursTransitionMode);
                }
                
                void ToursCameraTransitionController::TransitionBackToAppCamera(bool returnToOriginalMode)
                {
                    if(!returnToOriginalMode)
                    {
                        Eegeo::dv3 interestPoint;
                        Eegeo::v3 toInterestPoint;
                        
                        if(IsTransitioning())
                        {
                            toInterestPoint = m_toursCameraController.GetRenderCamera().GetModelMatrix().GetRow(2);
                            Eegeo_ASSERT(Eegeo::Geometry::IntersectionTests::GetRayEarthSphereIntersection(m_toursCameraController.GetCameraState().LocationEcef(),
                                                                                                           toInterestPoint,
                                                                                                           interestPoint),
                                         "Camera forward does not intersect with earth before transitioning out of tour mode");
                        }
                        else
                        {
                            toInterestPoint = Eegeo::dv3::ToSingle(interestPoint - m_toursCameraController.GetCameraState().LocationEcef());
                            interestPoint = m_toursCameraController.GetCameraState().InterestPointEcef();
                        }
                        
                        float distanceToInterest = (float)(interestPoint - m_toursCameraController.GetRenderCamera().GetEcefLocation()).Length();
                        
                        float terrainHeightAtInterest = 0.0f;
                        
                        if(m_terrainHeightProvider.TryGetHeight(interestPoint, 0, terrainHeightAtInterest))
                        {
                            interestPoint = interestPoint.Norm() * (Eegeo::Space::EarthConstants::Radius + terrainHeightAtInterest);
                        }
                        
                        Eegeo::Space::EcefTangentBasis ecefTangentBasis(interestPoint, toInterestPoint);
                        m_gpsGlobeCameraController.SetView(ecefTangentBasis, distanceToInterest);
                        
                        m_appCameraState = ToursCameraState::CreateFromCameraState(m_gpsGlobeCameraController.GetCameraState(), Eegeo::Math::Rad2Deg(m_gpsGlobeCameraController.GetRenderCamera().GetFOV()));
                    }
                    
                    if(IsTransitioning())
                    {
                        ToursCameraState currentTransitionCameraState(m_pToursTransitionMode->GetCurrentState());
                        Eegeo_DELETE m_pToursTransitionMode;
                        PerformCameraTransitionOrFade(currentTransitionCameraState, m_appCameraState);
                    }
                    else
                    {
                        PerformCameraTransitionOrFade(m_pToursCurrentMode->GetCurrentState(), m_appCameraState);
                    }
                    
                    m_toursCameraController.SetMode(m_pToursTransitionMode);
                    m_pToursNextMode = NULL;
                }
                
                void ToursCameraTransitionController::PerformCameraTransitionOrFade(const ToursCameraState& currentState,
                                                                                    const ToursCameraState& desiredState)
                {
                    
                    bool shouldAnimateCamera(ShouldPerformCameraSpline(currentState, desiredState));
                    
                    if(shouldAnimateCamera)
                    {
                        m_pToursTransitionMode = SplineTransitionCameraMode::CreateBetweenStates(currentState,
                                                                                                 desiredState);
                    }
                    else
                    {
                        // HACK SJM:: in future should probably make this take > 0 seconds and perform a fade to black and back.
                        // Right now just snap, would prefer to discuss how to implement fade, getting this in to fix crash bugs
                        // when running spline over too long a distance. Thinking about adding a FadeController or similar that
                        // the ToursCameraFadeTransitionMode can update?
                        const float fadeCeremonyTimeSeconds = 0.f;
                        m_pToursTransitionMode = Eegeo_NEW(ToursCameraFadeTransitionMode)(desiredState,
                                                                                          fadeCeremonyTimeSeconds);
                    }
                }
                
                bool ToursCameraTransitionController::ShouldPerformCameraSpline(const ToursCameraState& currentState,
                                                                                const ToursCameraState& desiredState)
                {
                    const double altitudeDelta = fabs(currentState.ecefPosition.Length() - desiredState.ecefPosition.Length());
                    const double maxSplineAltitudeDelta = 6000.f;
                    return altitudeDelta < maxSplineAltitudeDelta;
                }
            }
        }
    }
}
