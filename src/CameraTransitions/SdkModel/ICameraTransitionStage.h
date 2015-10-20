// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class ICameraTransitionStage
            {
            public:
                
                virtual ~ICameraTransitionStage() {}
                
                virtual void Start() = 0;
                virtual void Update(float dt) = 0;
                virtual void End() = 0;
                virtual const bool StageIsComplete() const = 0;
                virtual const bool StageHasFailed() const = 0;
            };
        }
    }
}