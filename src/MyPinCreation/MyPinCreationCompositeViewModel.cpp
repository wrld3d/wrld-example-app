// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "ISearchResultMenuViewModel.h"
#include "ISearchQueryPerformer.h"
#include "SearchResultsClearMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationCompositeViewModel::MyPinCreationCompositeViewModel(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
        															 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                                     IMyPinCreationInitiationViewModel& initiationViewModel,
                                                                     IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                                                     ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                                                     ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                                                     ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel)
        : m_stateChangeHandler(this, &MyPinCreationCompositeViewModel::OnPoiRingStateChanged)
        , m_searchResultMenuStateChangedCallback(this, &MyPinCreationCompositeViewModel::HandleSearchResultMenuStateChanged)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
        , m_initiationViewModel(initiationViewModel)
        , m_confirmationViewModel(confirmationViewModel)
        , m_primaryMenuViewModel(primaryMenuViewModel)
        , m_secondaryMenuViewModel(secondaryMenuViewModel)
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_searchResultMenuViewModel(searchResultMenuViewModel)
        {
            m_nativeToUiMessageBus.Subscribe(m_stateChangeHandler);
            m_searchResultMenuViewModel.InsertOnScreenStateChangedCallback(m_searchResultMenuStateChangedCallback);
        }
        
        MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
        {
            m_nativeToUiMessageBus.Unsubscribe(m_stateChangeHandler);
            m_searchResultMenuViewModel.RemoveOnScreenStateChangedCallback(m_searchResultMenuStateChangedCallback);
        }
        
        void MyPinCreationCompositeViewModel::OnPoiRingStateChanged(const ExampleApp::MyPinCreation::MyPinCreationStateChangedMessage &message)
        {
            switch (message.GetMyPinCreationStage())
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
                    
					//m_searchQueryPerformer.RemoveSearchQueryResults(); // <- The culprit. This be the changin' model thread!
                    m_uiToNativeMessageBus.Publish(Search::SearchResultsClearMessage());
                    m_searchResultMenuViewModel.RemoveFromScreen();
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
