// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "PoiCreation.h"
#include "PoiCreationStage.h"
#include "IPoiCreationCompositeViewModel.h"
#include "Menu.h"
#include "SearchResultMenu.h"
#include "ScreenControlViewModelBase.h"
#include "Search.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationCompositeViewModel : public IPoiCreationCompositeViewModel
        {
        public:
            
            PoiCreationCompositeViewModel(IPoiCreationModel& poiCreationModel,
                                          IPoiCreationButtonViewModel& buttonViewModel,
                                          IPoiCreationConfirmationViewModel& confirmationViewModel,
                                          ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                          ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                          ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                          ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel);
            
            ~PoiCreationCompositeViewModel();
            
            void HandlePoiRingStateChanged(PoiCreationStage& stage);
            void HandleSearchResultMenuStateChanged(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState);
            
        private:
            Eegeo::Helpers::ICallback1<PoiCreationStage>* m_pStateChangeCallback;
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pSearchResultMenuStateChangedCallback;
            
            IPoiCreationModel& m_poiCreationModel;
            IPoiCreationButtonViewModel& m_buttonViewModel;
            IPoiCreationConfirmationViewModel& m_confirmationViewModel;
            ExampleApp::Menu::IMenuViewModel& m_primaryMenuViewModel;
            ExampleApp::Menu::IMenuViewModel& m_secondaryMenuViewModel;
            
            ExampleApp::Search::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::Menu::IMenuViewModel& m_searchResultMenuViewModel;
        };
    }
}
