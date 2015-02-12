// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceDialogs.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				class InitialExperienceDialogsController
				{
				public:

					InitialExperienceDialogsController(
							IInitialExperienceDialogsView& view,
							IInitialExperienceDialogsViewModel& viewModel,
							ExampleAppMessaging::TMessageBus& messageBus);
					~InitialExperienceDialogsController();

				private:

					ExampleAppMessaging::TMessageBus& m_messageBus;
					IInitialExperienceDialogsView& m_view;
					IInitialExperienceDialogsViewModel& m_viewModel;

					Eegeo::Helpers::TCallback1<InitialExperienceDialogsController, const ShowInitialExperienceDialogMessage&> m_showDialogMessageHandler;
					Eegeo::Helpers::TCallback0<InitialExperienceDialogsController> m_viewOpened;
					Eegeo::Helpers::TCallback0<InitialExperienceDialogsController> m_viewClosed;
					Eegeo::Helpers::TCallback0<InitialExperienceDialogsController> m_viewCloseTapped;

					void OnShowDialog(const ShowInitialExperienceDialogMessage& message);
					void OnCloseTapped();
					void OnDialogOpened();
					void OnDialogClosed();
				};
			}

		}
	}
}
