// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "InitialExperience.h"
#include "ShowInitialExperienceIntroMessage.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroController
            {
            public:
             
                InitialExperienceIntroController(const std::shared_ptr<IInitialExperienceIntroView>& view,
                                                 const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                ~InitialExperienceIntroController();
                
            private:
                
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<IInitialExperienceIntroView> m_view;
                
                Eegeo::Helpers::TCallback1<InitialExperienceIntroController, const ShowInitialExperienceIntroMessage&> m_showIntroMessageHandler;
                Eegeo::Helpers::TCallback0<InitialExperienceIntroController> m_viewDismissed;
                
                void OnShowIntro(const ShowInitialExperienceIntroMessage& message);
                void OnViewDismissed();
            
            };
        }
    }
}