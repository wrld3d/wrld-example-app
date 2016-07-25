// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "Avatar.h"
#include "IAvatarModel.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class AvatarModel: public IAvatarModel
            {
            public:
                AvatarModel();
                
                ~AvatarModel();
                
                void Update(float dt);
                
                void SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& building);
                
                const Eegeo::Resources::Interiors::InteriorId& GetInteriorId();
                
                void SetFloor(int floor);
                
                int GetFloor();
                
                void SetPosition(const Eegeo::Space::LatLong& position);
                
                const Eegeo::Space::LatLong& GetPosition();
                
                const float GetHeading();
                void SetTargetPosition(const Eegeo::Space::LatLong& target);
                
                bool DestinationReached();
                
                bool GetAvatarVisibilityStatus(); // Retrun true if avatar is visbile
                
                void SetAvatarStatus(bool visibilityStatus);
                
                void AddAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                
                void AddAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                
                

                
            private:
                
                Eegeo::Helpers::CallbackCollection0 m_AvatarVisiblityCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_AvatarLocationChangeCallbacks;

                Eegeo::Resources::Interiors::InteriorId m_building;
                int m_floor;
                
                Eegeo::Space::LatLong m_currentLatLong;
                
                Eegeo::dv3 m_currentDirection;
                Eegeo::dv3 m_currentPos;
                Eegeo::dv3 m_targetPos;
                
                float m_time;
                float m_timeToReachDest;
                float m_velocity;
                
                float m_currentHeading;
                bool m_destinationReached;
                
                bool isAvatarShown;
                
                
            };
        }
    }
}
