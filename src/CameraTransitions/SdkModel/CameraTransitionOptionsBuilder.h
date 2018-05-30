// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CameraTransitions.h"
#include "CameraTransitionOptions.h"
#include "VectorMath.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class CameraTransitionOptionsBuilder
            {
            public:
                CameraTransitionOptionsBuilder();
                
                CameraTransitionOptionsBuilder(const CameraTransitionOptions& cameraTransitionOptions);
                
                CameraTransitionOptionsBuilder& SetInterestPoint(const Eegeo::dv3& interestPoint);
                CameraTransitionOptionsBuilder& SetDistanceFromInterest(float distanceFromInterest);
                CameraTransitionOptionsBuilder& SetHeadingRadians(float headingRadians, bool setHeadingInterior);
                
                CameraTransitionOptionsBuilder& SetIndoorPosition(const Eegeo::Resources::Interiors::InteriorId& interiorId, int targetFloorIndex);
                CameraTransitionOptionsBuilder& SetTargetFloorIndexIsFloorId(bool targetIndexIsFloorId);
                
                CameraTransitionOptionsBuilder& SetJumpIfFar(bool jumpIfFar);
                CameraTransitionOptionsBuilder& SetShouldDisableGps(bool shouldDisableGps);
                
                CameraTransitionOptions Build();
                
            private:
                Eegeo::dv3 m_interestPoint;
                float m_distanceFromInterest;
                float m_headingRadians;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_targetFloorIndex;
                bool m_targetFloorIndexIsFloorId;
                bool m_setHeading;
                bool m_setInteriorHeading;
                bool m_jumpIfFar;
                bool m_setGpsModeOff;
                bool m_setDistanceToInterest;
            };
        }
    }
}
