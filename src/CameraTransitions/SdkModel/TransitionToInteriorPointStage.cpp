// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TransitionToInteriorPointStage.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsCameraController.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorTransitionModel.h"


namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            TransitionToInteriorPointStage::TransitionToInteriorPointStage(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                           const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                           InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                           Eegeo::Resources::Interiors::InteriorsCameraController& cameraController,
                                                                           const Eegeo::dv3& newInterestPoint,
                                                                           float newDistanceToInterest,
                                                                           const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                                           int targetFloorIndex,
                                                                           bool jumpIfFar)
            : m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_cameraController(cameraController)
            , m_newInterestPoint(newInterestPoint)
            , m_targetDistanceToInterest(newDistanceToInterest)
            , m_transitionDuration(0.5f)
            , m_transitionTime(0.0f)
            , m_interiorId(interiorId)
            , m_targetFloorIndex(targetFloorIndex)
            , m_failed(false)
            , m_jumpIfFar(jumpIfFar)
            , m_startCameraInterestAltitude(0.0f)
            , m_endCameraInterestAltitude(0.0f)
            , m_initialisedNextInterior(false)
            , m_cameraInterestAltitudeStartTime(0.0f)
            {
            }
            
            void TransitionToInteriorPointStage::Start()
            {
                Eegeo_ASSERT(m_interiorInteractionModel.HasInteriorModel(), "Must be inside interior to start this transition");
                m_startCameraInterestAltitude = m_cameraController.GetFloorOffsetHeight();
                m_endCameraInterestAltitude = m_startCameraInterestAltitude;
                m_interiorSelectionModel.ClearSelection();
                m_interiorSelectionModel.SelectInteriorId(m_interiorId);
                m_interiorsExplorerModel.HideInteriorExplorer();
                m_transitionTime = 0.0f;
                m_startInterestPoint = m_cameraController.GetInterestLocation();
                m_startDistanceToInterest = m_cameraController.GetDistanceToInterest();
                m_cameraController.SetApplyRestrictions(false);
                m_cameraController.SetApplyFloorOffset(false);
                m_initialisedNextInterior = false;
                m_cameraInterestAltitudeStartTime = 0.0f;
            }
            
            void TransitionToInteriorPointStage::Update(float dt)
            {
                if(m_failed)
                {
                    return;
                }
                
                if(!m_initialisedNextInterior && m_interiorInteractionModel.HasInteriorModel())
                {
                    m_interiorInteractionModel.SetSelectedFloorIndex(m_targetFloorIndex);
                    m_endCameraInterestAltitude = m_cameraController.GetFloorOffsetHeight();
                    m_cameraInterestAltitudeStartTime = m_transitionTime;
                    m_initialisedNextInterior = true;
                }
                
                if(m_jumpIfFar && ShouldJumpTo(m_newInterestPoint))
                {
                    m_transitionTime = 1.01f;
                }
                else
                {
                    m_transitionTime += dt / m_transitionDuration;
                    float t = Eegeo::Math::Clamp01(m_transitionTime);
                    float smoothT = Eegeo::Math::SmoothStep(t);
                    Eegeo::dv3 lerpInterestPoint = Eegeo::dv3::Lerp(m_startInterestPoint, m_newInterestPoint, smoothT);
                    m_cameraController.SetInterestLocation(lerpInterestPoint);

                    float lerpDistance = Eegeo::Math::Lerp(m_startDistanceToInterest, m_targetDistanceToInterest, smoothT);
                    m_cameraController.SetDistanceToInterest(lerpDistance);

                    if(m_initialisedNextInterior)
                    {
                        float t2 = m_cameraInterestAltitudeStartTime >= 1.0f ? 1.0f : Eegeo::Math::Clamp01((m_transitionTime - m_cameraInterestAltitudeStartTime)/(1.0f-m_cameraInterestAltitudeStartTime));
                        float smoothT2 = Eegeo::Math::SmoothStep(t2);
                        float lerpAltitude = Eegeo::Math::Lerp(m_startCameraInterestAltitude, m_endCameraInterestAltitude, smoothT2);
                        m_cameraController.SetCameraInterestAltitude(lerpAltitude);
                    }
                }
                
                // Check fail condition and clean up on fail
                if(!m_interiorSelectionModel.IsInteriorSelected())
                {
                    m_failed = true;
                    m_cameraController.SetApplyRestrictions(true);
                    m_cameraController.SetApplyFloorOffset(true);
                }
                
            }
            
            void TransitionToInteriorPointStage::End()
            {
                m_cameraController.SetInterestLocation(m_newInterestPoint);
                m_cameraController.SetDistanceToInterest(m_targetDistanceToInterest);
                m_cameraController.SetCameraInterestAltitude(m_endCameraInterestAltitude);
                m_cameraController.SetApplyRestrictions(true);
                m_cameraController.SetApplyFloorOffset(true);
                m_interiorInteractionModel.SetSelectedFloorIndex(m_targetFloorIndex);
                m_interiorsExplorerModel.ShowInteriorExplorer(true);
            }
            
            const bool TransitionToInteriorPointStage::StageIsComplete() const
            {
                return m_transitionTime >= 1.0f && m_interiorTransitionModel.InteriorIsVisible();
            }
            
            bool TransitionToInteriorPointStage::ShouldJumpTo(Eegeo::dv3& newInterestPoint)
            {
                const double MAX_CAMERA_TRANSITION_DISTANCE = 500;
                Eegeo::dv3 currentInterestPoint = m_cameraController.GetInterestLocation();
                double distance = (newInterestPoint - currentInterestPoint).Length();
                return distance > MAX_CAMERA_TRANSITION_DISTANCE;
            }
            
            const bool TransitionToInteriorPointStage::StageHasFailed() const
            {
                return m_failed;
            }
        }
    }
}