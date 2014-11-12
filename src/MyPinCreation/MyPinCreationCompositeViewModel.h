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

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationCompositeViewModel : public IMyPinCreationCompositeViewModel
        {
        public:
            
            MyPinCreationCompositeViewModel(IMyPinCreationModel& MyPinCreationModel,
                                          IMyPinCreationInitiationViewModel& initiationViewModel,
                                          IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                          ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                          ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                          ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                          ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel);
            
            ~MyPinCreationCompositeViewModel();
            
            void HandlePoiRingStateChanged(MyPinCreationStage& stage);
            void HandleSearchResultMenuStateChanged(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState);
            
        private:
            Eegeo::Helpers::ICallback1<MyPinCreationStage>* m_pStateChangeCallback;
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pSearchResultMenuStateChangedCallback;
            
            IMyPinCreationModel& m_MyPinCreationModel;
            IMyPinCreationInitiationViewModel& m_initiationViewModel;
            IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
            ExampleApp::Menu::IMenuViewModel& m_primaryMenuViewModel;
            ExampleApp::Menu::IMenuViewModel& m_secondaryMenuViewModel;
            
            ExampleApp::Search::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::Menu::IMenuViewModel& m_searchResultMenuViewModel;
        };
    }
}
