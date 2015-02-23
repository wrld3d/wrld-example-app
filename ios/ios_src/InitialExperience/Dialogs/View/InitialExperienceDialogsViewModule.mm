// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsViewModule.h"
#include "InitialExperienceDialogsViewInterop.h"
#include "InitialExperienceDialogsController.h"
#include "InitialExperienceDialogsView.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace Dialogs
        {
            namespace View
            {
                InitialExperienceDialogsViewModule::InitialExperienceDialogsViewModule(IInitialExperienceDialogsViewModel& viewModel,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus)
                {
                    m_pView = [[InitialExperienceDialogsView alloc] initView];
                    m_pController = Eegeo_NEW(InitialExperienceDialogsController)(*[m_pView getInterop], viewModel, messageBus);
                }
                
                InitialExperienceDialogsViewModule::~InitialExperienceDialogsViewModule()
                {
                    
                }
                
                InitialExperienceDialogsView& InitialExperienceDialogsViewModule::GetDialogsView() const
                {
                    return *m_pView;
                }
                
                InitialExperienceDialogsController& InitialExperienceDialogsViewModule::GetDialogsController() const
                {
                    return *m_pController;
                }
            }
        }
    }
}
