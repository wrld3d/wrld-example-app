// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInitialExperienceDialogsViewModule.h"
#include "InitialExperienceDialogs.h"
#include "InitialExperienceDialogsViewIncludes.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace Dialogs
        {
            namespace View
            {
                class InitialExperienceDialogsViewModule : public IInitialExperienceDialogsViewModule, private Eegeo::NonCopyable
                {
                public:
                    InitialExperienceDialogsViewModule(IInitialExperienceDialogsViewModel& viewModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus);
                    ~InitialExperienceDialogsViewModule();
                    
                    InitialExperienceDialogsView& GetDialogsView() const;
                    InitialExperienceDialogsController& GetDialogsController() const;
                    
                private:
                    
                    InitialExperienceDialogsView* m_pView;
                    InitialExperienceDialogsController* m_pController;
                    
                };
            }
        }
    }
}
