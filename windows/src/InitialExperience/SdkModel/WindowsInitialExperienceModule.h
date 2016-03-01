// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include <jni.h>
#include "WindowsNativeState.h"
#include "InitialExperienceModuleBase.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "Menu.h"
//#include "SearchResultMenu.h"
//#include "InitialExperienceSearchResultAttractModeModule.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class WindowsInitialExperienceModule : public InitialExperienceModuleBase, private Eegeo::NonCopyable
            {
            public:
                WindowsInitialExperienceModule(
                    WindowsNativeState& m_nativeState,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~WindowsInitialExperienceModule();

            protected:
                std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel);

            private:
                WindowsNativeState& m_nativeState;
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
