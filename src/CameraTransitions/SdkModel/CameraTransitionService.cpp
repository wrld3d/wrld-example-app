// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CameraTransitionService.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            CameraTransitionService::CameraTransitionService()
            : m_pTransitionController(NULL)
            {
                
            }
            
            CameraTransitionService::~CameraTransitionService()
            {
                
            }
            
            void CameraTransitionService::SetTransitionController(ICameraTransitionController& transitionController)
            {
                m_pTransitionController = &transitionController;
            }
            
            const bool CameraTransitionService::HasValidController() const
            {
                return m_pTransitionController != NULL;
            }
            
            void CameraTransitionService::FailIfNoValidControllerSet()
            {
                Eegeo_ASSERT(HasValidController(), "No valid transition controller set");
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   float newHeadingRadians,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                   int targetFloorIndex,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   float newHeadingRadians,
                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                   int targetFloorIndex,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, interiorId, targetFloorIndex, jumpIfFar);
            }
            
            void CameraTransitionService::StopCurrentTransition()
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StopCurrentTransition();
            }
            
            void CameraTransitionService::Update(float dt)
            {
                if(HasValidController())
                {
                    m_pTransitionController->Update(dt);
                }
            }
            
            const bool CameraTransitionService::IsTransitioning() const
            {
                return HasValidController() ? m_pTransitionController->IsTransitioning() : false;
            }
        }
    }
}