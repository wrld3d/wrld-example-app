// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsController.h"
#include "InitialExperienceDialogDismissedMessage.h"
#include "IInitialExperienceDialogsView.h"
#include "IInitialExperienceDialogsViewModel.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				InitialExperienceDialogsController::InitialExperienceDialogsController(
					IInitialExperienceDialogsView& view,
					IInitialExperienceDialogsViewModel& viewModel,
					ExampleAppMessaging::TMessageBus& messageBus)
				: m_view(view)
				, m_viewModel(viewModel)
				, m_messageBus(messageBus)
				, m_showDialogMessageHandler(this, &InitialExperienceDialogsController::OnShowDialog)
				, m_viewClosed(this, &InitialExperienceDialogsController::OnDialogClosed)
				, m_viewOpened(this, &InitialExperienceDialogsController::OnDialogOpened)
				, m_viewCloseTapped(this, &InitialExperienceDialogsController::OnCloseTapped)
				{
					m_view.InsertCloseTappedCallback(m_viewCloseTapped);
					m_viewModel.InsertClosedCallback(m_viewClosed);
					m_viewModel.InsertOpenedCallback(m_viewOpened);
					m_messageBus.SubscribeUi(m_showDialogMessageHandler);
				}

				InitialExperienceDialogsController::~InitialExperienceDialogsController()
				{
					m_messageBus.UnsubscribeUi(m_showDialogMessageHandler);
					m_viewModel.RemoveOpenedCallback(m_viewOpened);
					m_viewModel.RemoveClosedCallback(m_viewClosed);
					m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
				}

				void InitialExperienceDialogsController::OnDialogOpened()
				{
					m_view.SetModalBackground(true);
					m_view.Open(m_viewModel.GetOpenType(), m_viewModel.GetTitle(), m_viewModel.GetDescription());
				}

				void InitialExperienceDialogsController::OnDialogClosed()
				{
					m_view.Close();
					if(m_viewModel.GetOpenType() == InitialExperienceDialogType::SourceCode)
					{
						m_view.SetModalBackground(false);
					}

					m_messageBus.Publish(InitialExperienceDialogDismissedMessage());
				}

				void InitialExperienceDialogsController::OnCloseTapped()
				{
					if (m_viewModel.IsOpen())
					{
						m_viewModel.Close();
					}
				}

				void InitialExperienceDialogsController::OnShowDialog(const ShowInitialExperienceDialogMessage& message)
				{
					m_viewModel.Open(message.DialogType());
				}
			}
		}
	}
}
