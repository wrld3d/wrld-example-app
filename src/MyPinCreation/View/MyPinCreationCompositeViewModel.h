// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "MyPinCreation.h"
#include "MyPinCreationStage.h"
#include "IMyPinCreationCompositeViewModel.h"
#include "Menu.h"
#include "SearchResultMenu.h"
#include "ScreenControlViewModelBase.h"
#include "Search.h"
#include "BidirectionalBus.h"
#include "MyPinCreationStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationCompositeViewModel : public IMyPinCreationCompositeViewModel
            {
            public:

                MyPinCreationCompositeViewModel(ExampleAppMessaging::TMessageBus& messageBus,
                                                IMyPinCreationInitiationViewModel& initiationViewModel,
                                                IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                                ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel);

                ~MyPinCreationCompositeViewModel();

                void HandlePoiRingStateChanged(MyPinCreationStage& stage);
                void OnPoiRingStateChangedMessage(const MyPinCreationStateChangedMessage& message);
                void HandleSearchResultMenuStateChanged(ScreenControl::View::IScreenControlViewModel &viewModel, float& onScreenState);

            private:
                Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, const MyPinCreationStateChangedMessage&> m_stateChangeHandler;
                Eegeo::Helpers::TCallback2<MyPinCreationCompositeViewModel, ScreenControl::View::IScreenControlViewModel&, float> m_searchResultMenuStateChangedCallback;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                IMyPinCreationInitiationViewModel& m_initiationViewModel;
                IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_secondaryMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_searchResultMenuViewModel;
            };
        }
    }
}
