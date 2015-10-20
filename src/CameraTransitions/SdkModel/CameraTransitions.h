// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class CameraTransitionService;
            class ICameraTransitionController;
            class ICameraTransitionStage;
            
            class TransitionToWorldPointStage;
            class ExitCurrentInteriorStage;
            class TransitionToInteriorStage;
        }
        
        class CameraTransitionChangedMessage;
    }
}
