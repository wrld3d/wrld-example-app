// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationCompositeViewModel.h"
#include "IPoiCreationModel.h"
#include "PoiCreationButtonViewModel.h"
#include "PoiCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "ISearchResultMenuViewModel.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationCompositeViewModel::PoiCreationCompositeViewModel(IPoiCreationModel& poiCreationModel,
                                                                     IPoiCreationButtonViewModel& buttonViewModel,
                                                                     IPoiCreationConfirmationViewModel& confirmationViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                                                     ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                                                     ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel)
        : m_pStateChangeCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<PoiCreationCompositeViewModel, PoiCreationStage>))(this, &PoiCreationCompositeViewModel::HandlePoiRingStateChanged))
        , m_pSearchResultMenuStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<PoiCreationCompositeViewModel, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &PoiCreationCompositeViewModel::HandleSearchResultMenuStateChanged))
        , m_poiCreationModel(poiCreationModel)
        , m_buttonViewModel(buttonViewModel)
        , m_confirmationViewModel(confirmationViewModel)
        , m_primaryMenuViewModel(primaryMenuViewModel)
        , m_secondaryMenuViewModel(secondaryMenuViewModel)
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_searchResultMenuViewModel(searchResultMenuViewModel)
        {
            m_poiCreationModel.AddStateChangedCallback(*m_pStateChangeCallback);
            m_searchResultMenuViewModel.InsertOnScreenStateChangedCallback(*m_pSearchResultMenuStateChangedCallback);
        }
        
        PoiCreationCompositeViewModel::~PoiCreationCompositeViewModel()
        {
            m_poiCreationModel.RemoveStateChangedCallback(*m_pStateChangeCallback);
            Eegeo_DELETE m_pStateChangeCallback;
            
            m_searchResultMenuViewModel.RemoveOnScreenStateChangedCallback(*m_pSearchResultMenuStateChangedCallback);
            Eegeo_DELETE m_pSearchResultMenuStateChangedCallback;
        }
        
        void PoiCreationCompositeViewModel::HandlePoiRingStateChanged(PoiCreationStage& stage)
        {
            switch (stage)
            {
                case Inactive:
                {
                    m_buttonViewModel.AddToScreen();
                    m_primaryMenuViewModel.AddToScreen();
                    m_secondaryMenuViewModel.AddToScreen();
                    
                    m_confirmationViewModel.RemoveFromScreen();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel.AddToScreen();
                    
                    m_buttonViewModel.RemoveFromScreen();
                    m_primaryMenuViewModel.RemoveFromScreen();
                    m_secondaryMenuViewModel.RemoveFromScreen();
                    
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    break;
                }
                case Details:
                {
                    break;
                }
                    
                default:
                {
                    Eegeo_ASSERT(false, "Invalid PoiCreationStage");
                }
        
            }
        }
        
        void PoiCreationCompositeViewModel::HandleSearchResultMenuStateChanged(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
        {
            if (viewModel.IsFullyOnScreen())
            {
                m_buttonViewModel.SetShouldOffsetViewButton(true);
                m_buttonViewModel.AddToScreen();
            }
            else
            {
                m_buttonViewModel.SetShouldOffsetViewButton(false);
                if (m_buttonViewModel.IsFullyOnScreen())
                {
                    m_buttonViewModel.AddToScreen();
                }
            }
        }
    }
}