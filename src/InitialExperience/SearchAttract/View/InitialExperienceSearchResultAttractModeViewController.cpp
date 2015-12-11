// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceSearchResultAttractModeViewController.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            namespace View
            {
                InitialExperienceSearchResultAttractModeViewController::InitialExperienceSearchResultAttractModeViewController(
                                                                                                                               Menu::View::IMenuViewModel& searchMenuViewModelControl,
                                                                                                                               /*SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,*/
                                                                                                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchMenuViewModelControl(searchMenuViewModelControl)
//                , m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_messageBus(messageBus)
                , m_shouldEnd(false)
                , m_finished(false)
                , m_onOpenableStateChanged(this, &InitialExperienceSearchResultAttractModeViewController::OnSearchResultMenuOpenStateChange)
                , m_onNativeStateEntered(this, &InitialExperienceSearchResultAttractModeViewController::OnNativeStateEntered)
                , m_onNativeStateUpdated(this, &InitialExperienceSearchResultAttractModeViewController::OnNativeStateUpdated)
                {
                    m_messageBus.SubscribeUi(m_onNativeStateEntered);
                    m_messageBus.SubscribeUi(m_onNativeStateUpdated);
                }
                
                InitialExperienceSearchResultAttractModeViewController::~InitialExperienceSearchResultAttractModeViewController()
                {
                    m_messageBus.UnsubscribeUi(m_onNativeStateUpdated);
                    m_messageBus.UnsubscribeUi(m_onNativeStateEntered);
                }
                
                void InitialExperienceSearchResultAttractModeViewController::EnterInitialExperienceUi()
                {
//                    m_searchMenuViewModelControl.InsertOpenStateChangedCallback(m_onOpenableStateChanged);
                    
                    SetAttractStateBaseOnInteractivity();
                }
                
                void InitialExperienceSearchResultAttractModeViewController::ExitInitialExperienceUi()
                {
//                    m_searchResultMenuViewModel.ExitAttractMode();
                    
//                    m_searchMenuViewModelControl.RemoveOpenStateChangedCallback(m_onOpenableStateChanged);
                    
                    m_messageBus.Publish(InitialExperienceSearchResultAttractModeModelStateExitedMessage());
                    
                    m_finished = true;
                }
                
                void InitialExperienceSearchResultAttractModeViewController::UpdateUi()
                {
                    if(!m_finished)
                    {
                        if(m_shouldEnd)
                        {
                            ExitInitialExperienceUi();
                        }
                        else
                        {
                            SetAttractStateBaseOnInteractivity();
                        }
                    }
                }
                
                void InitialExperienceSearchResultAttractModeViewController::SetAttractStateBaseOnInteractivity()
                {
                    /*if(m_searchResultMenuViewModel.CanInteract())
                    {
                        m_searchResultMenuViewModel.EnterAttractMode();
                    }
                    else
                    {
                        m_searchResultMenuViewModel.ExitAttractMode();
                    }*/
                }
                
                void InitialExperienceSearchResultAttractModeViewController::OnSearchResultMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
                {
                    /*if(m_searchMenuViewModelControl.IsFullyOpen())
                    {
                        m_shouldEnd = true;
                    }*/
                }
                
                void InitialExperienceSearchResultAttractModeViewController::OnNativeStateEntered(const InitialExperienceSearchResultAttractModeModelStateEnteredMessage& message)
                {
                    EnterInitialExperienceUi();
                }
                
                void InitialExperienceSearchResultAttractModeViewController::OnNativeStateUpdated(const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage& message)
                {
                    UpdateUi();
                }
            }
        }
    }
}