// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroController.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			InitialExperienceIntroViewModule::InitialExperienceIntroViewModule(AndroidNativeState& nativeState,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
																			   NavRouting::View::INavWidgetViewModel& navWidgetViewModel,
                                                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
			{
				m_pView = Eegeo_NEW(InitialExperienceIntroView)(nativeState, messageBus);
				m_pController = Eegeo_NEW(InitialExperienceIntroController)(*m_pView, messageBus, navWidgetViewModel, cameraTransitionController);
			}

			InitialExperienceIntroViewModule::~InitialExperienceIntroViewModule()
			{
				Eegeo_DELETE m_pController;
				Eegeo_DELETE m_pView;
			}
		}
	}
}
