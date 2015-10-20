// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TransitionToInteriorStage.h"
#include "InteriorController.h"
#include "InteriorSelectionModel.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            TransitionToInteriorStage::TransitionToInteriorStage(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& cameraController,
                                                                 const Eegeo::dv3& newInterestPoint,
                                                                 float newDistanceToInterest,
                                                                 const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                 int targetFloorIndex)
            : m_interiorController(interiorController)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_cameraController(cameraController)
            , m_newInterestPoint(newInterestPoint)
            , m_interiorId(interiorId)
            , m_targetFloorIndex(targetFloorIndex)
            , m_isAlreadyInInterior(interiorSelectionModel.GetSelectedInteriorId() == interiorId)
            , m_targetDistanceToInterest(newDistanceToInterest)
            , m_transitionDuration(0.5f)
            , m_transitionTime(0.0f)
            {
                Eegeo_ASSERT(m_interiorId != Eegeo::Resources::Interiors::InteriorId::NullId(), "Invalid Interior Id. Cannot transition to null interior");
            }
            
            void TransitionToInteriorStage::Start()
            {
                if(m_isAlreadyInInterior)
                {
                    m_transitionTime = 0.0f;
                    m_interiorController.SetCurrentFloor(m_targetFloorIndex);
                    m_startInterestPoint = m_cameraController.GetInterestLocation();
                    m_startDistanceToInterest = m_cameraController.GetDistanceToInterest();
                }
                else
                {
                    m_cameraController.SetInterestLocation(m_newInterestPoint);
                    m_cameraController.SetDistanceToInterest(m_targetDistanceToInterest);
                    m_interiorController.SetSelectedInterior(m_interiorId);
                }
            }
            
            void TransitionToInteriorStage::Update(float dt)
            {
                if(m_isAlreadyInInterior)
                {
                    m_transitionTime += dt/m_transitionDuration;
                    float t = Eegeo::Math::Clamp01(m_transitionTime);
                    float smoothT = Eegeo::Math::SmoothStep(t);
                    Eegeo::dv3 lerpInterestPoint = Eegeo::dv3::Lerp(m_startInterestPoint, m_newInterestPoint, smoothT);
                    m_cameraController.SetInterestLocation(lerpInterestPoint);
                    
                    float lerpDistance = Eegeo::Math::Lerp(m_startDistanceToInterest, m_targetDistanceToInterest, smoothT);
                    m_cameraController.SetDistanceToInterest(lerpDistance);
                }
                
                if(m_interiorController.InteriorInScene())
                {
                    m_interiorController.SetCurrentFloor(m_targetFloorIndex);
                }
            }
            
            void TransitionToInteriorStage::End()
            {
                m_cameraController.SetInterestLocation(m_newInterestPoint);
                m_cameraController.SetDistanceToInterest(m_targetDistanceToInterest);
            }
            
            const bool TransitionToInteriorStage::StageIsComplete() const
            {
                if(m_isAlreadyInInterior)
                {
                    return m_transitionTime >= 1.0f;
                }
                else return m_interiorController.InteriorIsVisible();
            }
            
            const bool TransitionToInteriorStage::StageHasFailed() const
            {
                // If an interior has been deselected via failure, we can no longer transition to one.
                return !m_interiorSelectionModel.IsInteriorSelected();
            }
        }
    }
}