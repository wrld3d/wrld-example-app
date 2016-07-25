// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "Avatar.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class IAvatarModule
            {
            public:
                
                virtual ~IAvatarModule() {}
                
                virtual IAvatarView& GetAvatarView() = 0;
                
                virtual IAvatarController& GetAvatarController() = 0;
                
                virtual IAvatarModel& GetAvatarModel() = 0;
                
                virtual void Update(float dt) = 0;
            };
        }
    }
}