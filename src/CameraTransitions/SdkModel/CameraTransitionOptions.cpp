// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CameraTransitionOptions.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            CameraTransitionOptions::CameraTransitionOptions(const Eegeo::dv3& interestPoint,
                                                             float distanceFromInterest,
                                                             float headingRadians,
                                                             const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                             int targetFloorIndex,
                                                             bool targetFloorIndexIsFloorId,
                                                             bool setHeading,
                                                             bool setInteriorHeading,
                                                             bool jumpIfFar,
                                                             bool setGpsModeOff,
                                                             bool setDistanceToInterest)
            : m_interestPoint(interestPoint)
            , m_distanceFromInterest(distanceFromInterest)
            , m_headingRadians(headingRadians)
            , m_interiorId(interiorId)
            , m_targetFloorIndex(targetFloorIndex)
            , m_targetFloorIndexIsFloorId(targetFloorIndexIsFloorId)
            , m_setHeading(setHeading)
            , m_setInteriorHeading(setInteriorHeading)
            , m_jumpIfFar(jumpIfFar)
            , m_setGpsModeOff(setGpsModeOff)
            , m_setDistanceToInterest(setDistanceToInterest)
            {
            }
        }
    }
}
