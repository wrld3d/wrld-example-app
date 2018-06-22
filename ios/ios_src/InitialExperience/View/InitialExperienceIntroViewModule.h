// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceIntroViewModule.h"
#include "InitialExperience.h"
#include "InitialExperienceIntroViewIncludes.h"
#include "BidirectionalBus.h"
#include "ScreenProperties.h"
#include "CameraTransitions.h"
#include "NavRouting.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroViewModule : public IInitialExperienceIntroViewModule
            {
            public:
                
                InitialExperienceIntroViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                 NavRouting::View::INavWidgetViewModel& navWidgetViewModel,
                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                 const Eegeo::Rendering::ScreenProperties& screenProperties);
                ~InitialExperienceIntroViewModule();
                
                InitialExperienceIntroController& GetIntroViewController() const
                {
                    return *m_pController;
                }
                
                InitialExperienceIntroView& GetIntroView() const
                {
                    return *m_pView;
                }
                
                InitialExperienceIntroBackgroundView& GetIntroBackgroundView() const
                {
                    return *m_pBackgroundView;
                }
                
            private:
                
                InitialExperienceIntroController* m_pController;
                InitialExperienceIntroView* m_pView;
                InitialExperienceIntroBackgroundView* m_pBackgroundView;
            };
        }
    }
}
