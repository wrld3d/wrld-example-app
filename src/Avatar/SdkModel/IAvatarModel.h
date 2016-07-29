// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class IAvatarModel
            {
            public:
                virtual ~IAvatarModel() { }
                
                virtual void Update(float dt) = 0;
                
                virtual void SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& building) = 0;
                
                virtual const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() = 0;
                
                virtual void SetFloor(int floor) = 0;
                
                virtual int GetFloor() = 0;
                
                virtual void SetPosition(const Eegeo::Space::LatLong& target) = 0;
                
                virtual const Eegeo::Space::LatLong& GetPosition() = 0;
                
                virtual const float GetHeading() = 0;

                
                virtual void SetTargetPosition(const Eegeo::Space::LatLong& target) = 0;
                
                virtual bool DestinationReached() = 0;
                
                virtual bool GetAvatarVisibilityStatus() = 0;
                
                virtual void SetAvatarStatus(bool visibilityStatus)= 0;
                
                virtual void ResetAvatarModel() = 0;

                
                virtual void AddAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveAvatarVisiblityChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                
                virtual void AddAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveAvatarLocationChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}