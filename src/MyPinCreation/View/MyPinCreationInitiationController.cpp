// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationController.h"
#include "IMyPinCreationInitiationView.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationController::MyPinCreationInitiationController(
                IMyPinCreationInitiationViewModel& viewModel,
                IMyPinCreationInitiationView& view,
                IMyPinCreationConfirmationViewModel& confirmationViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_confirmationViewModel(confirmationViewModel)
                , m_messageBus(messageBus)
                , m_selectedCallback(this, &MyPinCreationInitiationController::OnSelected)
                , m_viewStateCallback(this, &MyPinCreationInitiationController::OnViewStateChangeScreenControl)
            {
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
            }

            MyPinCreationInitiationController::~MyPinCreationInitiationController()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
            }

            void MyPinCreationInitiationController::OnSelected()
            {
                if(m_confirmationViewModel.TryOpen())
                {
                    MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Ring);
                    m_messageBus.Publish(message);
                }
            }

            void MyPinCreationInitiationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                m_view.ShouldOffsetButton(m_viewModel.ShouldOffsetViewButton());

                ScreenControl::View::Apply(m_viewModel, m_view);
            }
        }
    }
}
