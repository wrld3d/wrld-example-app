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
                    const std::shared_ptr<WindowsNativeState>& m_nativeState,
                    const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                    const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>& worldAreaLoaderModel,
                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus
                );

                ~WindowsInitialExperienceModule();

            protected:
                std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel);

            private:
                const std::shared_ptr<WindowsNativeState> m_nativeState;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
            };
        }
    }
}
