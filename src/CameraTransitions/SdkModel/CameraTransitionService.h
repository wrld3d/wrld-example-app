// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CameraTransitions.h"
#include "ICameraTransitionController.h"
#include "Types.h"
#include "Interiors.h"
#include "VectorMath.h"
#include "CallbackCollection.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class CameraTransitionService : public ICameraTransitionController, protected Eegeo::NonCopyable
            {
            public:
                
                CameraTransitionService();
                ~CameraTransitionService();
                
                void SetTransitionController(ICameraTransitionController& transitionController);
                
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       bool jumpIfFar=true);
                
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       float newHeadingRadians,
                                       bool jumpIfFar=true);
                
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true);
                void StartTransitionTo(float distanceFromInterest,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true);
   
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       float newHeadingRadians,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true,
                                       bool setGpsModeOff=true,
                                       bool setInteriorHeading=false,
                                       bool setDistanceToInterest=true);
                
                void StopCurrentTransition();
                void Update(float dt);
                
                const bool IsTransitioning() const;
                const bool HasValidController() const;
                
                void InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback);
                
            private:
                
                void OnTransitioningChanged();
                
                void FailIfNoValidControllerSet();
                
                ICameraTransitionController* m_pTransitionController;
                
                Eegeo::Helpers::CallbackCollection0 m_transitioningChangedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_transitionCompletedCallbacks;
                Eegeo::Helpers::TCallback0<CameraTransitionService> m_transitioningChangedHandler;
            };
        }
    }
}