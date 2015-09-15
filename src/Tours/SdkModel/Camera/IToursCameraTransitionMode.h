// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraMode.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraTransitionMode : public IToursCameraMode
                {
                public:
                    
                    virtual ~IToursCameraTransitionMode() {}
                    
                    virtual bool HasEnded() const = 0;
                };
            }
        }
    }
}