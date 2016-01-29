// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerCameraController.h"

#include "CameraHelpers.h"
#include "EarthConstants.h"
#include "GlobeCameraTouchController.h"
#include "GlobeCameraController.h"
#include "InteriorController.h"
#include "InteriorMarkerModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorsModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "CurrentInteriorViewModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorHeightHelpers.h"
#include "GlobeCameraController.h"
#include "EnvironmentFlatteningService.h"
#include "CurrentInteriorViewModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace
            {
                float CalcFloorHeightAboveBase(const Eegeo::Resources::Interiors::InteriorsModel& model, int floorIndex)
                {
                    return ExampleApp::Helpers::InteriorHeightHelpers::INTERIOR_FLOOR_HEIGHT * floorIndex;
                }
            }
            
            
            InteriorsExplorerCameraController::InteriorsExplorerCameraController(
                                                                Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                                Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                                                const bool interiorsAffectedByFlattening)
            : m_interiorController(interiorController)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_globeCameraTouchController(globeCameraTouchController)
            , m_globeCameraController(globeCameraController)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_cameraTouchEnabled(false)
            , m_interiorsAffectedByFlattening(interiorsAffectedByFlattening)
            , m_applyRestrictions(true)
            , m_cameraInterestAltitude(0)
            , m_applyFloorOffset(true)
            {
                // Temp manually set initial cam pos.
                Eegeo::Space::EcefTangentBasis basis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(Eegeo::Space::LatLong::FromDegrees(0, 0).ToECEF(), 0.0f, basis);
                m_globeCameraController.SetView(basis, 100.0f);
                m_globeCameraController.ApplyTilt(15.0f);
            }
            
            InteriorsExplorerCameraController::~InteriorsExplorerCameraController()
            {
            }
            
            const Eegeo::Camera::CameraState InteriorsExplorerCameraController::GetCameraState() const
            {
                return m_globeCameraController.GetCameraState();
            }
            
            const Eegeo::Camera::RenderCamera InteriorsExplorerCameraController::GetRenderCamera() const
            {
                return m_globeCameraController.GetRenderCamera();
            }
            
            Eegeo::dv3 InteriorsExplorerCameraController::ComputeNonFlattenedCameraPosition() const
            {
                const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                if(!m_interiorController.TryGetCurrentModel(pModel))
                {
                    return m_globeCameraController.ComputeNonFlattenedCameraPosition();
                }
                
                float baseHeight = pModel->GetTangentSpaceBounds().GetMin().y;
                float floorOffsetHeight = GetFloorOffsetHeight();
                float altitude = (baseHeight + floorOffsetHeight);
                Eegeo::dv3 unflattenedInterestPos = m_globeCameraController.GetEcefInterestPoint().Norm() * (Eegeo::Space::EarthConstants::Radius + altitude);
                
                Eegeo::dv3 cameraPos;
                Eegeo::v3 cameraDir;
                Eegeo::v3 cameraUp;
                Eegeo::Camera::CameraHelpers::CalculateLookAt(unflattenedInterestPos,
                                                              m_globeCameraController.GetInterestBasis().GetForward(),
                                                              Eegeo::Math::Deg2Rad( m_globeCameraController.CalculatePitchDegrees()),
                                                              m_globeCameraController.GetDistanceToInterest(),
                                                              cameraPos,
                                                              cameraDir,
                                                              cameraUp);
                
                return cameraPos;
            }
            
            Eegeo::ITouchController& InteriorsExplorerCameraController::GetTouchController() const
            {
                return m_globeCameraTouchController;
            }
            
            void InteriorsExplorerCameraController::Update(float dt)
            {
                if(!m_interiorSelectionModel.IsInteriorSelected())
                {
                    return;
                }
                
                m_cameraTouchEnabled = m_interiorController.InteriorIsVisible();
                
                if(m_cameraTouchEnabled)
                {
                    m_globeCameraTouchController.Update(dt);
                }
                else
                {
                    m_globeCameraTouchController.Reset();
                }
                
                m_globeCameraController.Update(dt);
                
                if(m_interiorController.InteriorInScene())
                {
                    Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel = NULL;
                    m_interiorController.TryGetCurrentViewModel(pViewModel);
                    bool expanded = pViewModel->GetExpandedModeEnabled();
                    float expandedParam = pViewModel->GetExpandedModeParameter();
                    

                    if(!expanded && expandedParam == 0.0f)
                    {
                        m_normalDistanceToInterest = m_globeCameraController.GetDistanceToInterest();
                        m_normalTilt = 15.0f; // Can't get current tilt - Might have to manually calculate it which is a bit arse.
                    }
                    
                    Eegeo::dv3 cameraInterestEcef = m_globeCameraController.GetInterestBasis().GetPointEcef();
                    Eegeo::dv3 initialCameraInterestEcef = cameraInterestEcef;
                    cameraInterestEcef = cameraInterestEcef.Norm() * Eegeo::Space::EarthConstants::Radius;

                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    Eegeo_ASSERT(m_interiorController.TryGetCurrentModel(pModel));

                    if(m_applyFloorOffset)
                    {
                        m_cameraInterestAltitude = GetFloorOffsetHeight();
                    }

                    const Eegeo::Space::EcefTangentBasis& interiorTangentBasis = pModel->GetTangentBasis();
                    Eegeo::dv3 origin = interiorTangentBasis.GetPointEcef();
                    
                    Eegeo::v3 relativeCameraInterestEcef = (cameraInterestEcef - origin).ToSingle();
                    Eegeo::v3 cameraInterestTangentSpace = Eegeo::v3::MulRotate(relativeCameraInterestEcef, interiorTangentBasis.GetEcefToTangentTransform());
                    cameraInterestTangentSpace.y = m_cameraInterestAltitude;
                    
                    // Expanded view interest position.
                    // TODO: Maybe subtly slide position up and down based on floor param and number of floors.
                    float floorGap = Eegeo::v2(pModel->GetTangentSpaceBounds().Size().x, pModel->GetTangentSpaceBounds().Size().z).Length()*0.25f;
                    float centerHeight = floorGap * pModel->GetFloorCount()*0.5f;
                    const Eegeo::Geometry::Bounds3D& tangentSpaceBounds = pModel->GetTangentSpaceBounds();
                    
                    Eegeo::v3 tangentSpaceOriginPoint = Eegeo::v3(tangentSpaceBounds.Center().x,
                                                                  (tangentSpaceBounds.GetMin().y*m_environmentFlatteningService.GetCurrentScale()) + centerHeight,
                                                                  tangentSpaceBounds.Center().z);

                    cameraInterestTangentSpace = Eegeo::v3::Lerp(cameraInterestTangentSpace, tangentSpaceOriginPoint, expandedParam);
                    
                    // Zoom for expanded view
                    // TODO: Bit of hackery here, coming up with a one-size solution is a bit tricky.
                    // Current solution is... alright?
                    float expandedZoom = (centerHeight) / Eegeo::Math::Tan(m_globeCameraController.GetRenderCamera().GetFOV()*0.5f)*1.75f;
                    float zoom = Eegeo::Math::Lerp(m_normalDistanceToInterest, expandedZoom, expandedParam);
                    float tilt = Eegeo::Math::Lerp(m_normalTilt, 0.0f, expandedParam);
                    m_globeCameraController.SetView(m_globeCameraController.GetInterestBasis(), zoom);
                    m_globeCameraController.ApplyTilt(tilt);
                    
                    if(m_applyRestrictions &&
                       (cameraInterestTangentSpace.x > tangentSpaceBounds.GetMax().x ||
                       cameraInterestTangentSpace.x < tangentSpaceBounds.GetMin().x ||
                       cameraInterestTangentSpace.z > tangentSpaceBounds.GetMax().z ||
                       cameraInterestTangentSpace.z < tangentSpaceBounds.GetMin().z))
                    {
                        Eegeo::v3 clampedPoint = Eegeo::v3::Min(Eegeo::v3::Max(cameraInterestTangentSpace, tangentSpaceBounds.GetMin()), tangentSpaceBounds.GetMax());
                        cameraInterestTangentSpace.x = clampedPoint.x;
                        cameraInterestTangentSpace.z = clampedPoint.z;
                    }
                    
                    Eegeo::m33 tangentBasis;
                    pModel->GetTangentBasis().GetBasisOrientationAsMatrix(tangentBasis);
                    relativeCameraInterestEcef = Eegeo::v3::Mul(cameraInterestTangentSpace, tangentBasis);
                    
                    Eegeo::dv3 finalEcefInterestPosition;
                    Eegeo::dv3 interiorOriginAtBase = pModel->GetTangentBasis().GetPointEcef() + pModel->GetTangentBasis().GetUp() * pModel->GetTangentSpaceBounds().GetMin().y;
                    if(!m_interiorsAffectedByFlattening)
                    {
                        finalEcefInterestPosition = m_environmentFlatteningService.GetScaledPointEcef(interiorOriginAtBase, m_environmentFlatteningService.GetCurrentScale()) + relativeCameraInterestEcef;
                    }
                    else
                    {
                        finalEcefInterestPosition = m_environmentFlatteningService.GetScaledPointEcef(interiorOriginAtBase + relativeCameraInterestEcef, m_environmentFlatteningService.GetCurrentScale());
                    }
                    
                    const double PositionUpdateThresholdDistanceSq = 0.01;
                    if((finalEcefInterestPosition - initialCameraInterestEcef).LengthSq() > PositionUpdateThresholdDistanceSq)
                    {
                        SetInterestLocation(finalEcefInterestPosition);
                    }
                }
            }
            
            void InteriorsExplorerCameraController::SetInterestLocation(const Eegeo::dv3& interestPointEcef)
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis = m_globeCameraController.GetInterestBasis();
                cameraInterestBasis.SetPoint(interestPointEcef);
                m_globeCameraController.SetInterestBasis(cameraInterestBasis);
            }
            
            const Eegeo::dv3& InteriorsExplorerCameraController::GetInterestLocation() const
            {
                return m_globeCameraController.GetInterestBasis().GetPointEcef();
            }
            
            void InteriorsExplorerCameraController::SetDistanceToInterest(float distanceMeters)
            {
                m_globeCameraController.SetView(m_globeCameraController.GetInterestBasis(), distanceMeters);
            }
            
            const float InteriorsExplorerCameraController::GetDistanceToInterest() const
            {
                return m_globeCameraController.GetDistanceToInterest();
            }
            
            void InteriorsExplorerCameraController::SetHeading(float headingDegrees)
            {
                const Eegeo::dv3& ecefInterestPoint = m_globeCameraController.GetInterestBasis().GetPointEcef();
                
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(ecefInterestPoint, headingDegrees, cameraInterestBasis);
                m_globeCameraController.SetView(cameraInterestBasis, m_globeCameraController.GetDistanceToInterest());
            }
            
            float InteriorsExplorerCameraController::GetHeadingDegrees() const
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_globeCameraController.GetInterestBasis().GetPointEcef(),
                                                                                               m_globeCameraController.GetInterestBasis().GetForward());
                
                return Eegeo::Math::Rad2Deg(headingRadians);
            }
            
            void InteriorsExplorerCameraController::SetTilt(float tiltDegrees)
            {
                m_globeCameraController.ApplyTilt(tiltDegrees);
            }
            
            void InteriorsExplorerCameraController::SetApplyRestrictions(bool applyRestrictions)
            {
                m_applyRestrictions = applyRestrictions;
            }
   
            void InteriorsExplorerCameraController::SetApplyFloorOffset(bool applyFloorOffset)
            {
                m_applyFloorOffset = applyFloorOffset;
            }
            
            float InteriorsExplorerCameraController::GetCameraInterestAltitude() const
            {
                return m_cameraInterestAltitude;
            }
            void InteriorsExplorerCameraController::SetCameraInterestAltitude(float cameraInterestAltitude)
            {
                m_cameraInterestAltitude = cameraInterestAltitude;
            }
            
            float InteriorsExplorerCameraController::GetFloorOffsetHeight() const
            {
                Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel = NULL;
                Eegeo_ASSERT(m_interiorController.TryGetCurrentViewModel(pViewModel), "Failed to get Interior Viewmodel");
                
                float interpolatedFloorValue = pViewModel->GetFloorParameter();
                
                const int targetFloorA = (int)std::floor(interpolatedFloorValue);
                const int targetFloorB = (int)std::ceil(interpolatedFloorValue);
                const float interfloorParam = interpolatedFloorValue - (float)targetFloorA;
                
                float floorOffsetA = CalcFloorHeightAboveBase(pViewModel->GetModel(), targetFloorA);
                float floorOffsetB = CalcFloorHeightAboveBase(pViewModel->GetModel(), targetFloorB);
                
                float floorOffset = Eegeo::Math::Lerp(floorOffsetA, floorOffsetB, interfloorParam);
                return floorOffset;
                
            }
            
            Eegeo::Camera::GlobeCamera::GlobeCameraController& InteriorsExplorerCameraController::GetGlobeCameraController()
            {
                return m_globeCameraController;
            }
        }
    }
}