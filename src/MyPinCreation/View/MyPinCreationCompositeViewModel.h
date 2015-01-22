// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "MyPinCreation.h"
#include "MyPinCreationStage.h"
#include "IMyPinCreationCompositeViewModel.h"
#include "Menu.h"
#include "SearchResultMenu.h"
#include "ScreenControlViewModelBase.h"
#include "Search.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"
#include "MyPinCreationStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationCompositeViewModel : public IMyPinCreationCompositeViewModel
        {
        public:
            
            MyPinCreationCompositeViewModel(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
            							  ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                          IMyPinCreationInitiationViewModel& initiationViewModel,
                                          IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                          ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                          ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                          ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                          ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel);
            
            ~MyPinCreationCompositeViewModel();
            
            void HandlePoiRingStateChanged(MyPinCreationStage& stage);
            void OnPoiRingStateChanged(const MyPinCreationStateChangedMessage& message);
            void HandleSearchResultMenuStateChanged(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState);
            
        private:
            Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, const MyPinCreationStateChangedMessage&> m_stateChangeHandler;
            Eegeo::Helpers::TCallback2<MyPinCreationCompositeViewModel, ScreenControlViewModel::IScreenControlViewModel&, float> m_searchResultMenuStateChangedCallback;
            
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            IMyPinCreationInitiationViewModel& m_initiationViewModel;
            IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
            ExampleApp::Menu::IMenuViewModel& m_primaryMenuViewModel;
            ExampleApp::Menu::IMenuViewModel& m_secondaryMenuViewModel;
            
            ExampleApp::Search::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::Menu::IMenuViewModel& m_searchResultMenuViewModel;
        };
    }
}
