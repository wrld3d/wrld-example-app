// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>
#include "AndroidNativeState.h"
#include "InitialExperienceModuleBase.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class AndroidInitialExperienceModule : public InitialExperienceModuleBase, private Eegeo::NonCopyable
            {
            public:
                AndroidInitialExperienceModule(
						const std::shared_ptr<AndroidNativeState>& nativeState,
                        const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                        const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>& worldAreaLoaderModel,
                        const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus
                );

                ~AndroidInitialExperienceModule();

            protected:
                std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel);

            private:
                const std::shared_ptr<AndroidNativeState> m_nativeState;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
            };
        }
    }
}
