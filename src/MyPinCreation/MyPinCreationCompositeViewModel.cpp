// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinCreationModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "ISearchResultMenuViewModel.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationCompositeViewModel::MyPinCreationCompositeViewModel(IMyPinCreationModel& MyPinCreationModel,
                                                                     IMyPinCreationInitiationViewModel& initiationViewModel,
                                                                     IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                                                     ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                                                     ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel)
        : m_pStateChangeCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, MyPinCreationStage>))(this, &MyPinCreationCompositeViewModel::HandlePoiRingStateChanged))
        , m_pSearchResultMenuStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MyPinCreationCompositeViewModel, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &MyPinCreationCompositeViewModel::HandleSearchResultMenuStateChanged))
        , m_MyPinCreationModel(MyPinCreationModel)
        , m_initiationViewModel(initiationViewModel)
        , m_confirmationViewModel(confirmationViewModel)
        , m_primaryMenuViewModel(primaryMenuViewModel)
        , m_secondaryMenuViewModel(secondaryMenuViewModel)
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_searchResultMenuViewModel(searchResultMenuViewModel)
        {
            m_MyPinCreationModel.AddStateChangedCallback(*m_pStateChangeCallback);
            m_searchResultMenuViewModel.InsertOnScreenStateChangedCallback(*m_pSearchResultMenuStateChangedCallback);
        }
        
        MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
        {
            m_MyPinCreationModel.RemoveStateChangedCallback(*m_pStateChangeCallback);
            Eegeo_DELETE m_pStateChangeCallback;
            
            m_searchResultMenuViewModel.RemoveOnScreenStateChangedCallback(*m_pSearchResultMenuStateChangedCallback);
            Eegeo_DELETE m_pSearchResultMenuStateChangedCallback;
        }
        
        void MyPinCreationCompositeViewModel::HandlePoiRingStateChanged(MyPinCreationStage& stage)
        {
            switch (stage)
            {
                case Inactive:
                {
                    m_initiationViewModel.AddToScreen();
                    m_primaryMenuViewModel.AddToScreen();
                    m_secondaryMenuViewModel.AddToScreen();
                    
                    m_confirmationViewModel.RemoveFromScreen();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel.AddToScreen();
                    
                    m_initiationViewModel.RemoveFromScreen();
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
                    Eegeo_ASSERT(false, "Invalid MyPinCreationStage");
                }
        
            }
        }
        
        void MyPinCreationCompositeViewModel::HandleSearchResultMenuStateChanged(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
        {
            if (viewModel.IsFullyOnScreen())
            {
                m_initiationViewModel.SetShouldOffsetViewButton(true);
                m_initiationViewModel.AddToScreen();
            }
            else
            {
                m_initiationViewModel.SetShouldOffsetViewButton(false);
                if (m_initiationViewModel.IsFullyOnScreen())
                {
                    m_initiationViewModel.AddToScreen();
                }
            }
        }
    }
}