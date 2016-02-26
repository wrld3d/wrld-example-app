// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceModuleBase.h"
#include "InitialExperience.h"
#include "InitialExperienceModel.h"
#include "InitialExperienceController.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            InitialExperienceModuleBase::InitialExperienceModuleBase(PersistentSettings::IPersistentSettingsModel& persistentSettings)
                : m_pInitialExperienceModel(NULL)
                , m_pInitialExperienceController(NULL)
                , m_persistentSettings(persistentSettings)
            {
            }

            InitialExperienceModuleBase::~InitialExperienceModuleBase()
            {
                TearDown();
            }

            PersistentSettings::IPersistentSettingsModel& InitialExperienceModuleBase::GetPersistentSettings() const
            {
                return m_persistentSettings;
            }

            void InitialExperienceModuleBase::InitialiseWithApplicationModels(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel)
            {
                Eegeo_ASSERT(m_pInitialExperienceModel == NULL, "Cannot call InitialExperienceModule::InitialiseWithApplicationModels twice.\n");

                std::vector<IInitialExperienceStep*> steps = CreateSteps(worldAreaLoaderModel);

                const int lastCameraLockedStep = 0;
                
                m_pInitialExperienceModel = Eegeo_NEW(InitialExperienceModel)(steps, lastCameraLockedStep);

                m_pInitialExperienceController = Eegeo_NEW(InitialExperienceController)(*m_pInitialExperienceModel);
            }

            void InitialExperienceModuleBase::TearDown()
            {
                Eegeo_DELETE m_pInitialExperienceController;
                m_pInitialExperienceController = NULL;

                Eegeo_DELETE m_pInitialExperienceModel;
                m_pInitialExperienceModel = NULL;
            }

            IInitialExperienceModel& InitialExperienceModuleBase::GetInitialExperienceModel() const
            {
                Eegeo_ASSERT(m_pInitialExperienceModel != NULL, "Must call InitialExperienceModule::InitialiseWithApplicationModels before accessing model.\n");
                return *m_pInitialExperienceModel;
            }

            IInitialExperienceController& InitialExperienceModuleBase::GetInitialExperienceController() const
            {
                Eegeo_ASSERT(m_pInitialExperienceController != NULL, "Must call InitialExperienceModule::InitialiseWithApplicationModels before accessing controller.\n");
                return *m_pInitialExperienceController;
            }
        }
    }
}
