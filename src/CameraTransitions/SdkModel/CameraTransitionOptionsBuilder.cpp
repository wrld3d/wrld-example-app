// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CameraTransitionOptionsBuilder.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {

            CameraTransitionOptionsBuilder::CameraTransitionOptionsBuilder()
            : m_interestPoint(Eegeo::dv3::Zero())
            , m_distanceFromInterest(0)
            , m_setDistanceToInterest(false)
            , m_headingRadians(0)
            , m_setHeading(false)
            , m_setInteriorHeading(false)
            , m_interiorId("")
            , m_targetFloorIndex(0)
            , m_targetFloorIndexIsFloorId(false)
            , m_setGpsModeOff(true)
            , m_jumpIfFar(true)
            {
                
            }
            
            CameraTransitionOptionsBuilder::CameraTransitionOptionsBuilder(const CameraTransitionOptions& other)
            : m_interestPoint(other.GetInterestPoint())
            , m_distanceFromInterest(other.GetDistanceFromInterest())
            , m_headingRadians(other.GetHeadingRadians())
            , m_interiorId(other.GetInteriorId())
            , m_targetFloorIndex(other.GetTargetFloorIndex())
            , m_targetFloorIndexIsFloorId(other.IsTargetFloorIndexFloorId())
            , m_setHeading(other.ShouldSetHeading())
            , m_setInteriorHeading(other.ShouldSetInteriorHeading())
            , m_jumpIfFar(other.ShouldJumpIfFar())
            , m_setGpsModeOff(other.ShouldDisableGPS())
            , m_setDistanceToInterest(other.GetDistanceFromInterest())
            {
                
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetInterestPoint(const Eegeo::dv3& interestPoint)
            {
                m_interestPoint = interestPoint;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetDistanceFromInterest(float distanceFromInterest)
            {
                m_distanceFromInterest = distanceFromInterest;
                m_setDistanceToInterest = true;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetHeadingRadians(float headingRadians,
                                                                                              bool setHeadingInterior)
            {
                m_headingRadians = headingRadians;
                m_setHeading = true;
                m_setInteriorHeading = setHeadingInterior;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetIndoorPosition(const Eegeo::Resources::Interiors::InteriorId& interiorId, int targetFloorIndex)
            {
                m_interiorId = interiorId;
                m_targetFloorIndex = targetFloorIndex;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetTargetFloorIndexIsFloorId(bool targetIndexIsFloorId)
            {
                m_targetFloorIndexIsFloorId = targetIndexIsFloorId;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetJumpIfFar(bool jumpIfFar)
            {
                m_jumpIfFar = jumpIfFar;
                return *this;
            }
            
            CameraTransitionOptionsBuilder& CameraTransitionOptionsBuilder::SetShouldDisableGps(bool shouldDisableGps)
            {
                m_setGpsModeOff = shouldDisableGps;
                return *this;
            }
            
            CameraTransitionOptions CameraTransitionOptionsBuilder::Build()
            {
                return CameraTransitionOptions(m_interestPoint,
                                               m_distanceFromInterest,
                                               m_headingRadians,
                                               m_interiorId,
                                               m_targetFloorIndex,
                                               m_targetFloorIndexIsFloorId,
                                               m_setHeading,
                                               m_setInteriorHeading,
                                               m_jumpIfFar,
                                               m_setGpsModeOff,
                                               m_setDistanceToInterest);
            }
        }
    }
}
