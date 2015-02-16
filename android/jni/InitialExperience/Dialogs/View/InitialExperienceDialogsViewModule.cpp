// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsViewModule.h"
#include "InitialExperienceDialogsView.h"
#include "InitialExperienceDialogsController.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				InitialExperienceDialogsViewModule::InitialExperienceDialogsViewModule(
						AndroidNativeState& nativeState,
						IInitialExperienceDialogsViewModel& viewModel,
						ExampleAppMessaging::TMessageBus& messageBus)
				{
					m_pView = Eegeo_NEW(InitialExperienceDialogsView)(nativeState);
					m_pController = Eegeo_NEW(InitialExperienceDialogsController)(*m_pView, viewModel, messageBus);
				}

				InitialExperienceDialogsViewModule::~InitialExperienceDialogsViewModule()
				{
					Eegeo_DELETE m_pController;
					Eegeo_DELETE m_pView;
				}
			}
		}
	}
}
