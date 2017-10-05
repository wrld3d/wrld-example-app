// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"
#include "Interiors.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class ICameraTransitionController
            {
            public:

                virtual ~ICameraTransitionController() {};

                virtual void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                               float distanceFromInterest,
                                               bool jumpIfFar=true) = 0;
                
                virtual void StartTransitionTo(float distanceFromInterest,
                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                               int targetFloorIndex,
                                               bool jumpIfFar=true) = 0;

                virtual void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                               float distanceFromInterest,
                                               float newHeadingRadians,
                                               bool jumpIfFar=true) = 0;
                
                virtual void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                               float distanceFromInterest,
                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                               int targetFloorIndex,
                                               bool jumpIfFar=true) = 0;
                
                virtual void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                               float distanceFromInterest,
                                               float newHeadingRadians,
                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                               int targetFloorIndex,
                                               bool jumpIfFar=true,
                                               bool setGpsModeOff=true,
                                               bool setInteriorHeading=false,
                                               bool setDistanceToInterest=true) = 0;
                
                virtual void StopCurrentTransition() = 0;
                virtual void Update(float dt) = 0;

                virtual const bool IsTransitioning() const = 0;
                
                virtual void InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
