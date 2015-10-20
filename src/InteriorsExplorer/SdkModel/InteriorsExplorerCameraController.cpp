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

#include "GlobeCameraController.h"

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
                    float modelBaseAltitude = model.GetTangentSpaceBounds().GetMin().y;
                    float floorAltitude = model.GetFloorAtIndex(floorIndex).GetTangentSpaceBounds().Center().y;
                    float floorHeightAboveBase = floorAltitude - modelBaseAltitude;
                    
                    return floorHeightAboveBase;
                }
            }
            
            
            InteriorsExplorerCameraController::InteriorsExplorerCameraController(
                                                                Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                                Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
            : m_interiorController(interiorController)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_markerRepository(markerRepository)
            , m_globeCameraTouchController(globeCameraTouchController)
            , m_globeCameraController(globeCameraController)
            , m_cameraTouchEnabled(false)
            {
                // Temp manually set initial cam pos.
                Eegeo::Space::EcefTangentBasis basis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(Eegeo::Space::LatLong::FromDegrees(0, 0).ToECEF(), 0.0f, basis);
                m_globeCameraController.SetView(basis, 100.0f);
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
                    Eegeo::dv3 cameraInterestEcef = m_globeCameraController.GetInterestBasis().GetPointEcef();
                    cameraInterestEcef = cameraInterestEcef.Norm() * Eegeo::Space::EarthConstants::Radius;
                    
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    Eegeo_ASSERT(m_interiorController.TryGetCurrentModel(pModel));
                    
                    Eegeo::v3 relativeCameraInterestEcef = (cameraInterestEcef - pModel->GetTangentBasis().GetPointEcef()).ToSingle();
                    
                    Eegeo::v3 cameraInterestTangentSpace = Eegeo::v3(Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetRight()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetUp()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetForward()));
                    
                    float tangentBoundsHalfWidth = (pModel->GetTangentSpaceBounds().GetMax().x - pModel->GetTangentSpaceBounds().GetMin().x)*0.5f;
                    float tangentBoundsHalfLength = (pModel->GetTangentSpaceBounds().GetMax().z - pModel->GetTangentSpaceBounds().GetMin().z)*0.5f;
                    
                    float cameraInterestAltitude = GetFloorOffsetHeight();
                    
                    cameraInterestTangentSpace.Set(cameraInterestTangentSpace.x, cameraInterestAltitude, cameraInterestTangentSpace.z);

                    if(cameraInterestTangentSpace.x < -tangentBoundsHalfWidth ||
                       cameraInterestTangentSpace.x > tangentBoundsHalfWidth ||
                       cameraInterestTangentSpace.z < -tangentBoundsHalfLength ||
                       cameraInterestTangentSpace.z > tangentBoundsHalfLength)
                    {
                        float newX = Eegeo::Math::Clamp(cameraInterestTangentSpace.x, -tangentBoundsHalfWidth, tangentBoundsHalfWidth);
                        float newZ = Eegeo::Math::Clamp(cameraInterestTangentSpace.z, -tangentBoundsHalfLength, tangentBoundsHalfLength);
                        cameraInterestTangentSpace.Set(newX, cameraInterestAltitude, newZ);
                    }
                    
                    Eegeo::m33 tangentBasis;
                    pModel->GetTangentBasis().GetBasisOrientationAsMatrix(tangentBasis);
                    relativeCameraInterestEcef = Eegeo::v3::Mul(cameraInterestTangentSpace, tangentBasis);
                    
                    SetInterestLocation(pModel->GetTangentBasis().GetPointEcef() + relativeCameraInterestEcef);
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
            
            const float InteriorsExplorerCameraController::GetHeadingDegrees() const
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_globeCameraController.GetInterestBasis().GetPointEcef(),
                                                                                               m_globeCameraController.GetRenderCamera().GetModelMatrix().GetRow(2));
                
                return Eegeo::Math::Rad2Deg(headingRadians);
            }
            
            void InteriorsExplorerCameraController::SetTilt(float tiltDegrees)
            {
                m_globeCameraController.ApplyTilt(tiltDegrees);
            }
            
            float InteriorsExplorerCameraController::GetFloorOffsetHeight() const
            {
                const Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel = NULL;
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