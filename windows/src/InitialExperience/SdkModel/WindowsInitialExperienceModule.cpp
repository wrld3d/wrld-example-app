// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsInitialExperienceModule.h"
#include "WindowsInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"
//#include "InitialExperienceSearchResultAttractModeModel.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            WindowsInitialExperienceModule::WindowsInitialExperienceModule(
                const std::shared_ptr<WindowsNativeState>& nativeState,
                const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>& worldAreaLoaderModel,
                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus
            )
                : InitialExperienceModuleBase(persistentSettings, worldAreaLoaderModel)
                , m_nativeState(nativeState)
                , m_messageBus(messageBus)
            {

            }

            WindowsInitialExperienceModule::~WindowsInitialExperienceModule()
            {
            }

            std::vector<IInitialExperienceStep*> WindowsInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel)
            {
                std::vector<IInitialExperienceStep*> steps;

                m_messageBus->Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));

                return steps;
            }
        }
    }
}
