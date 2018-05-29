// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class CameraTransitionOptions
            {
            public:
                
                CameraTransitionOptions(const Eegeo::dv3& interestPoint,
                                        float distanceFromInterest,
                                        float headingRadians,
                                        const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                        int targetFloorIndex,
                                        bool targetFloorIndexIsFloorId,
                                        bool setHeading,
                                        bool setInteriorHeading,
                                        bool jumpIfFar,
                                        bool setGpsModeOff,
                                        bool setDistanceToInterest);
                
                const Eegeo::dv3& GetInterestPoint() const { return m_interestPoint; }
                
                float GetDistanceFromInterest() const { return m_distanceFromInterest; }
                bool ShouldSetDistanceToInterest() const { return m_setDistanceToInterest; }
                
                float GetHeadingRadians() const { return m_headingRadians; }
                bool ShouldSetHeading() const { return m_setHeading; }
                bool ShouldSetInteriorHeading() const { return m_setInteriorHeading; }
                
                const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return m_interiorId; }
                int GetTargetFloorIndex() const { return m_targetFloorIndex; }
                bool IsTargetFloorIndexFloorId() const { return m_targetFloorIndexIsFloorId; }
                
                bool ShouldJumpIfFar() const { return m_jumpIfFar; }
                bool ShouldDisableGPS() const { return m_setGpsModeOff; }
                
                
            private:
                const Eegeo::dv3 m_interestPoint;
                float m_distanceFromInterest;
                float m_headingRadians;
                const Eegeo::Resources::Interiors::InteriorId m_interiorId;
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
