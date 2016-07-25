// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "Avatar.h"
#include "Space.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class IAvatarController
            {
            public:
                
                virtual ~IAvatarController() {}
                
                virtual void SetModelTarget(const Eegeo::Space::LatLong& latLong, const Eegeo::Resources::Interiors::InteriorId& building, int floor) = 0;
                
                virtual void Update(float dt) = 0;
                
            };
        }
    }
}