// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CameraTransitionService.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            CameraTransitionService::CameraTransitionService(const std::shared_ptr<CameraTransitionController>& cameraTransitionController)
            : m_cameraTransitionController(cameraTransitionController)
            , m_transitioningChangedHandler(this, &CameraTransitionService::OnTransitioningChanged)
            {
                m_cameraTransitionController->InsertTransitioningChangedCallback(m_transitioningChangedHandler);
            }
            
            CameraTransitionService::~CameraTransitionService()
            {
                m_cameraTransitionController->RemoveTransitioningChangedCallback(m_transitioningChangedHandler);
            }

            const bool CameraTransitionService::HasValidController() const
            {
                return m_cameraTransitionController != nullptr;
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
                m_cameraTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   float newHeadingRadians,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_cameraTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                   int targetFloorIndex,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_cameraTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                   float distanceFromInterest,
                                   float newHeadingRadians,
                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                   int targetFloorIndex,
                                   bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_cameraTransitionController->StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, interiorId, targetFloorIndex, jumpIfFar);
            }
            
            void CameraTransitionService::StartTransitionTo(float distanceFromInterest,
                                                            const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                            int targetFloorIndex,
                                                            bool jumpIfFar)
            {
                FailIfNoValidControllerSet();
                m_cameraTransitionController->StartTransitionTo(distanceFromInterest, interiorId, targetFloorIndex);
            }

            
            void CameraTransitionService::StopCurrentTransition()
            {
                FailIfNoValidControllerSet();
                m_cameraTransitionController->StopCurrentTransition();
            }
            
            void CameraTransitionService::Update(float dt)
            {
                if(HasValidController())
                {
                    m_cameraTransitionController->Update(dt);
                }
            }
            
            const bool CameraTransitionService::IsTransitioning() const
            {
                return HasValidController() ? m_cameraTransitionController->IsTransitioning() : false;
            }
            
            void CameraTransitionService::InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.AddCallback(callback);
            }
            void CameraTransitionService::RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.RemoveCallback(callback);
            }
            
            void CameraTransitionService::OnTransitioningChanged()
            {
                m_transitioningChangedCallbacks.ExecuteCallbacks();
            }
        }
    }
}