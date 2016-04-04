// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TransitionToInteriorStage.h"
#include "InteriorSelectionModel.h"
#include "InteriorId.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorsCameraController.h"
#include "InteriorTransitionModel.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            TransitionToInteriorStage::TransitionToInteriorStage(
                                                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                 Eegeo::Resources::Interiors::InteriorsCameraController& cameraController,
                                                                 const Eegeo::dv3& newInterestPoint,
                                                                 float newDistanceToInterest,
                                                                 const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                 int targetFloorIndex)
            : m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_cameraController(cameraController)
            , m_newInterestPoint(newInterestPoint)
            , m_interiorId(interiorId)
            , m_targetFloorIndex(targetFloorIndex)
            , m_alreadySelectedInterior(interiorSelectionModel.GetSelectedInteriorId() == interiorId)
            , m_targetDistanceToInterest(newDistanceToInterest)
            , m_transitionDuration(0.5f)
            , m_transitionTime(0.0f)
            {
                Eegeo_ASSERT(m_interiorId != Eegeo::Resources::Interiors::InteriorId::NullId(), "Invalid Interior Id. Cannot transition to null interior");
            }
            
            void TransitionToInteriorStage::Start()
            {
                if(!m_alreadySelectedInterior)
                {
                    m_cameraController.SetInterestLocation(m_newInterestPoint);
                    m_cameraController.SetDistanceToInterest(InteriorsExplorer::DefaultInteriorTransitionInterestDistance);
                    m_interiorSelectionModel.SelectInteriorId(m_interiorId);
                }
                else if(m_interiorInteractionModel.HasInteriorModel())
                {
                    m_interiorInteractionModel.SetSelectedFloorIndex(m_targetFloorIndex);
                }
                
                m_transitionTime = 0.0f;
                m_startInterestPoint = m_cameraController.GetInterestLocation();
                m_startDistanceToInterest = m_cameraController.GetDistanceToInterest();
            }
            
            void TransitionToInteriorStage::Update(float dt)
            {
                if(m_interiorTransitionModel.InteriorIsVisible())
                {
                    m_transitionTime += dt/m_transitionDuration;
                    float t = Eegeo::Math::Clamp01(m_transitionTime);
                    float smoothT = Eegeo::Math::SmoothStep(t);
                    Eegeo::dv3 lerpInterestPoint = Eegeo::dv3::Lerp(m_startInterestPoint, m_newInterestPoint, smoothT);
                    m_cameraController.SetInterestLocation(lerpInterestPoint);
                    
                    float lerpDistance = Eegeo::Math::Lerp(m_startDistanceToInterest, m_targetDistanceToInterest, smoothT);
                    m_cameraController.SetDistanceToInterest(lerpDistance);
                }
                
                if(m_interiorInteractionModel.HasInteriorModel())
                {
                    m_interiorInteractionModel.SetSelectedFloorIndex(m_targetFloorIndex);
                }
            }
            
            void TransitionToInteriorStage::End()
            {
                m_cameraController.SetInterestLocation(m_newInterestPoint);
                m_cameraController.SetDistanceToInterest(m_targetDistanceToInterest);
            }
            
            const bool TransitionToInteriorStage::StageIsComplete() const
            {
                return m_interiorTransitionModel.InteriorIsVisible() && m_transitionTime >= 1.0f;
            }
            
            const bool TransitionToInteriorStage::StageHasFailed() const
            {
                // If an interior has been deselected via failure, we can no longer transition to one.
                return !m_interiorSelectionModel.IsInteriorSelected();
            }
        }
    }
}