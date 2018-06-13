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
            , m_transitioningChangedHandler(this, &CameraTransitionService::OnTransitioningChanged)
            , m_transitionCompleteHandler(this, &CameraTransitionService::OnTransitioningCompleted)
            , m_transitionFailedHandler(this, &CameraTransitionService::OnTransitioningFailed)
            {
                
            }
            
            CameraTransitionService::~CameraTransitionService()
            {
                if(HasValidController())
                {
                    m_pTransitionController->RemoveTransitioningChangedCallback(m_transitioningChangedHandler);
                    m_pTransitionController->RemoveTransitionCompletedCallback(m_transitionCompleteHandler);
                    m_pTransitionController->RemoveTransitionFailedCallback(m_transitionFailedHandler);
                }
            }
            
            void CameraTransitionService::SetTransitionController(ICameraTransitionController& transitionController)
            {
                if(HasValidController())
                {
                    m_pTransitionController->RemoveTransitioningChangedCallback(m_transitioningChangedHandler);
                    m_pTransitionController->RemoveTransitionCompletedCallback(m_transitionCompleteHandler);
                    m_pTransitionController->RemoveTransitionFailedCallback(m_transitionFailedHandler);
                }
                m_pTransitionController = &transitionController;
                m_pTransitionController->InsertTransitioningChangedCallback(m_transitioningChangedHandler);
                m_pTransitionController->InsertTransitionCompletedCallback(m_transitionCompleteHandler);
                m_pTransitionController->InsertTransitionFailedCallback(m_transitionFailedHandler);
            }
            
            const bool CameraTransitionService::HasValidController() const
            {
                return m_pTransitionController != NULL;
            }
            
            void CameraTransitionService::FailIfNoValidControllerSet()
            {
                Eegeo_ASSERT(HasValidController(), "No valid transition controller set");
            }
            
            void CameraTransitionService::StartTransition(const CameraTransitionOptions& options)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransition(options);
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
                                                            bool jumpIfFar,
                                                            bool setGpsModeOff,
                                                            bool setInteriorHeading,
                                                            bool setDistanceToInterest)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, interiorId, targetFloorIndex, jumpIfFar, setGpsModeOff, setInteriorHeading, setDistanceToInterest);
            }
            
            void CameraTransitionService::StartTransitionTo(float distanceFromInterest,
                                                            const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                            int targetFloorIndex,
                                                            bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_pTransitionController->StartTransitionTo(distanceFromInterest, interiorId, targetFloorIndex);
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
            
            void CameraTransitionService::InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.AddCallback(callback);
            }
            void CameraTransitionService::RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.RemoveCallback(callback);
            }

            void CameraTransitionService::InsertTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionCompletedCallbacks.AddCallback(callback);
            }
            void CameraTransitionService::RemoveTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionCompletedCallbacks.RemoveCallback(callback);
            }

            void CameraTransitionService::InsertTransitionFailedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionFailedCallbacks.AddCallback(callback);
            }

            void CameraTransitionService::RemoveTransitionFailedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionFailedCallbacks.AddCallback(callback);
            }
            
            void CameraTransitionService::OnTransitioningChanged()
            {
                m_transitioningChangedCallbacks.ExecuteCallbacks();
            }

            void CameraTransitionService::OnTransitioningCompleted()
            {
                m_transitionCompletedCallbacks.ExecuteCallbacks();
            }

            void CameraTransitionService::OnTransitioningFailed()
            {
                m_transitionFailedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
