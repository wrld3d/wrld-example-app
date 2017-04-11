// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceViewIncludes.h"
#include "InitialExperience.h"
#include "WindowsNativeState.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroViewModule
            {
            public:
                InitialExperienceIntroViewModule(WindowsNativeState& nativeState,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 bool isInKioskMode,
                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                ~InitialExperienceIntroViewModule();

                InitialExperienceIntroController& GetController() { return *m_pController; }

            private:

                InitialExperienceIntroController* m_pController;
                InitialExperienceIntroView* m_pView;
            };
        }
    }
}
