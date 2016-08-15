// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "InitialExperienceModuleBase.h"
#include "InitialExperience.h"
#include "PersistentSettings.h"
#include "BidirectionalBus.h"
#include "Menu.h"
#include <memory>

namespace ExampleApp
{
    namespace InitialExperience
    {
        class iOSInitialExperienceModule : public SdkModel::InitialExperienceModuleBase, private Eegeo::NonCopyable
        {
        public:
            iOSInitialExperienceModule(const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

            ~iOSInitialExperienceModule();

        protected:

            std::vector<SdkModel::IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel);
            
            const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
        };
    }
}
