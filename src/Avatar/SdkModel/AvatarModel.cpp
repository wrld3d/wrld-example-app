	// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarModel.h"
#include "Types.h"

#include "IAvatarController.h"
#include "EcefTangentBasis.h"
#include "MathFunc.h"
#include "SceneModel.h"
#include "SceneModelAnimator.h"
#include "SceneModelLoader.h"
#include "SceneModelRenderableFilter.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            AvatarModel::AvatarModel()
            : m_building("")
            , m_floor(0)
            , m_currentLatLong(0.0f, 0.0f)
            , m_currentDirection(0.0f, 1.0f, 0.0f)
            , m_targetPos(0.0f, 0.0f, 0.0f)
            , m_currentPos(0.0f, 0.0f, 0.0f)
            , m_currentHeading(0.0f)
            , m_destinationReached(true)
            , m_time(0.0f)
            , m_timeToReachDest(0.0f)
            , m_velocity(4.0f)
            {
            }
            
            AvatarModel::~AvatarModel()
            {
            }
            
            void AvatarModel::Update(float dt)
            {
                
                if(m_destinationReached)
                {
                    return;
                }
                
                m_time += dt;
                
                if(m_time < m_timeToReachDest)
                {
                    m_currentPos = m_currentPos + (m_currentDirection * m_velocity * dt);
                }
                else
                {
                    m_currentPos = m_targetPos;
                    m_destinationReached = true;
                }
                
                m_currentLatLong = Eegeo::Space::LatLong::FromECEF(m_currentPos);
                m_AvatarLocationChangeCallbacks.ExecuteCallbacks();

            }
            
            void AvatarModel::SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& building)
            {
                m_building = building;
            }
            
            const Eegeo::Resources::Interiors::InteriorId& AvatarModel::GetInteriorId()
            {
                return m_building;
            }
            
            void AvatarModel::SetFloor(int floor)
            {
                m_floor = floor;
            }
            
            int AvatarModel::GetFloor()
            {
                return m_floor;
            }
            
            bool AvatarModel::DestinationReached()
            {
                return m_destinationReached;
            }
            
            bool AvatarModel::GetAvatarVisibilityStatus() {
                
                return isAvatarShown;
            }
            void AvatarModel::SetAvatarStatus(bool visibilityStatus) {
                
                isAvatarShown = visibilityStatus;
                m_AvatarVisiblityCallbacks.ExecuteCallbacks();
            }
            
            void AvatarModel::SetPosition(const Eegeo::Space::LatLong& position)
            {
                m_currentPos = position.ToECEF();
                m_currentLatLong = Eegeo::Space::LatLong::FromECEF(m_currentPos);
                m_time = 0.0f;
            }
            
            const Eegeo::Space::LatLong& AvatarModel::GetPosition()
            {
                return m_currentLatLong;
            }
            
            const float AvatarModel::GetHeading()
            {
                return m_currentHeading;
            }
            void AvatarModel::SetTargetPosition(const Eegeo::Space::LatLong& target)
            {
                m_targetPos = target.ToECEF();
                
                if(m_currentPos.LengthSq() == 0.0)
                {
                    SetPosition(target);
                }
                
                Eegeo::dv3 heading = m_targetPos - m_currentPos;
                
                m_timeToReachDest = 0.0f;
                
                m_time = 0.0f;
                
                float distance = static_cast<float>(heading.Length());
                
                const float minDistThreshold = 1.0f;
                
                if(m_destinationReached && distance < minDistThreshold)
                {
                    return;
                }
                else if(distance > 0.0f)
                {
                    m_currentDirection = heading /distance;
                    
                    m_destinationReached = false;
                    
                    m_timeToReachDest = distance / m_velocity;
                }
                
                Eegeo::dv3 northHeading = Eegeo::dv3(0.0f, 1.0f, 0.0f);
                
                const Eegeo::dv3 Up = m_currentPos.Norm();
                
                const Eegeo::dv3 right = Eegeo::dv3::Cross(m_currentPos.Norm(), northHeading).Norm();
                
                northHeading = Eegeo::dv3::Cross(right, Up);
                
                double  dot = Eegeo::dv3::Dot( northHeading, m_currentDirection);
                
                float headingInRads = Eegeo::Math::ACos(static_cast<float>(dot));
                m_currentHeading = Eegeo::Math::Rad2Deg(headingInRads);
                
                if(Eegeo::dv3::Dot(m_currentDirection, right) < 0.0f)
                {
                    m_currentHeading = -m_currentHeading;
                }
                m_AvatarLocationChangeCallbacks.ExecuteCallbacks();
              

                
                Eegeo_ASSERT(m_currentHeading == m_currentHeading, "heading created returned NaN, currentDirection.x = %f and 1/x = %f", m_currentDirection.x, 1/m_currentDirection.x);
            }
            
            void AvatarModel::ResetAvatarModel() {
                
                m_currentLatLong = Eegeo::Space::LatLong(0.0f,0.0f);
                
                m_currentDirection = Eegeo::dv3(0.0f, 1.0f, 0.0f);
                
                m_targetPos = Eegeo::dv3(0.0f, 0.0f, 0.0f);
                
                m_currentPos = Eegeo::dv3(0.0f, 0.0f, 0.0f);;
                
                m_currentHeading = 0.0f;

                m_destinationReached = true;

                m_time = 0.0f;

                m_timeToReachDest = 0.0f;
                
                m_velocity = 4.0f;

            }
            
            void AvatarModel::AddAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_AvatarVisiblityCallbacks.AddCallback(callback);
            }
            void AvatarModel::RemoveAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_AvatarVisiblityCallbacks.RemoveCallback(callback);
            }
            
            void AvatarModel::AddAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_AvatarLocationChangeCallbacks.AddCallback(callback);
            }
            void AvatarModel::RemoveAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_AvatarLocationChangeCallbacks.RemoveCallback(callback);
            }
        }
    }
}
