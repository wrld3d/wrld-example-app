// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationController : private Eegeo::NonCopyable
            {
            public:
                MyPinCreationInitiationController(IMyPinCreationInitiationViewModel& viewModel,
                                                  IMyPinCreationInitiationView& view,
                                                  IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                ~MyPinCreationInitiationController();

                void OnSelected();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

            private:

                IMyPinCreationInitiationViewModel& m_viewModel;
                IMyPinCreationInitiationView& m_view;
                IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback2<MyPinCreationInitiationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationInitiationController> m_selectedCallback;
            };
        }
    }
}
