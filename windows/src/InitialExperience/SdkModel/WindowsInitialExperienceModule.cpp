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
                WindowsNativeState& nativeState,
                PersistentSettings::IPersistentSettingsModel& persistentSettings,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : InitialExperienceModuleBase(persistentSettings)
                , m_nativeState(nativeState)
                , m_messageBus(messageBus)
                //, m_pInitialExperienceSearchResultAttractModeModule(NULL)
            {

            }

            WindowsInitialExperienceModule::~WindowsInitialExperienceModule()
            {
                //Eegeo_DELETE m_pInitialExperienceSearchResultAttractModeModule;
            }

            std::vector<IInitialExperienceStep*> WindowsInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel)
            {
                std::vector<IInitialExperienceStep*> steps;

				// TODO: Recreate MEA initial experience steps for windows...
				
				m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));

                return steps;
            }
        }
    }
}
