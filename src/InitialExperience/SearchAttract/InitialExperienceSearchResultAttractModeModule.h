// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "Types.h"
//#include "ISearchResultMenuViewModel.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"
#include "IPersistentSettingsModel.h"
#include "BidirectionalBus.h"
#include "InitialExperienceSearchResultAttractModeModel.h"
#include "InitialExperienceSearchResultAttractModeViewController.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            class InitialExperienceSearchResultAttractModeModule : private Eegeo::NonCopyable
            {
            public:
                InitialExperienceSearchResultAttractModeModule(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                               Menu::View::IMenuViewModel& searchMenuViewModelControl,
//                                                               SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                               ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InitialExperienceSearchResultAttractModeModule();
                
                InitialExperience::SdkModel::IInitialExperienceStep& GetInitialExperienceStep();
                
            private:
                SdkModel::InitialExperienceSearchResultAttractModeModel* m_pInitialExperienceSearchResultAttractModeModel;
                View::InitialExperienceSearchResultAttractModeViewController* m_pInitialExperienceSearchResultAttractModeViewController;
            };
        }
    }
}