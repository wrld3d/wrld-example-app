// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class IAvatarView
            {
            public:
                
                virtual ~IAvatarView() {}
                
                virtual void SetLatLongHeading(const Eegeo::Space::LatLong& latLong, const float headingDegrees) = 0;
                
                virtual void SetHeightAboveSeaLevel(float heightAboveSeaLevel) = 0;
                
                virtual void StartMoving() = 0;
                virtual void StopMoving() = 0;
                
                virtual void HideAvatar() = 0;
                virtual void ShowAvatar() = 0;
                
                virtual bool IsShowingAvatar() = 0;
                
                virtual void Update(float dt) = 0;
            };
        }
    }
}
