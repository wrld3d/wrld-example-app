// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultMenuViewModel.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"
#include "BidirectionalBus.h"
#include "InitialExperienceSearchResultAttractModeModelStateEnteredMessage.h"
#include "InitialExperienceSearchResultAttractModeModelStateUpdatedMessage.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            namespace View
            {
                class InitialExperienceSearchResultAttractModeViewController : private Eegeo::NonCopyable
                {
                public:
                    InitialExperienceSearchResultAttractModeViewController(Menu::View::IMenuViewModel& searchMenuViewModelControl,
                                                                           SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                                           ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~InitialExperienceSearchResultAttractModeViewController();
                    
                    void OnSearchResultMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                    
                    void SetAttractStateBaseOnInteractivity();
                    
                    void EnterInitialExperienceUi();
                    
                    void UpdateUi();
                    
                    void ExitInitialExperienceUi();
                    
                    void OnNativeStateEntered(const InitialExperienceSearchResultAttractModeModelStateEnteredMessage& message);
                    
                    void OnNativeStateUpdated(const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage& message);
                    
                private:
                    Menu::View::IMenuViewModel& m_searchMenuViewModelControl;
                    SearchResultMenu::View::ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    bool m_shouldEnd;
                    bool m_finished;
                    
                    Eegeo::Helpers::TCallback2<InitialExperienceSearchResultAttractModeViewController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenableStateChanged;
                    
                    Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeViewController, const InitialExperienceSearchResultAttractModeModelStateEnteredMessage&> m_onNativeStateEntered;
                    
                    Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeViewController, const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage&> m_onNativeStateUpdated;
                };
            }
        }
    }
}