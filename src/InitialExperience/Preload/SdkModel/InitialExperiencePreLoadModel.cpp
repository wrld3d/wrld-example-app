// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "InitialExperiencePreLoadModelBase.h"
#include "IInitialExperienceStep.h"
#include "IWorldAreaLoaderModel.h"
#include "IPersistentSettingsModel.h"
#include "PreloadSphereVolume.h"

namespace
{
    const std::string InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_StartedKey = "InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_StartedKey";

    const std::string InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_CompletedKey = "InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_CompletedKey";

    bool GetKeyValue(ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings, const std::string& key)
    {
        bool result = false;

        if(!persistentSettings.TryGetValue(key, result))
        {
            result = false;
        }

        return result;
    }
}

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                InitialExperiencePreLoadModelBase::InitialExperiencePreLoadModelBase(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                        PersistentSettings::IPersistentSettingsModel& persistentSettings)
                    : m_worldAreaLoaderModel(worldAreaLoaderModel)
                    , m_persistentSettings(persistentSettings)
                    , m_pPreloadCompleteCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<InitialExperiencePreLoadModelBase>)(this, &InitialExperiencePreLoadModelBase::HandlePreloadComplete))
                {
                    m_worldAreaLoaderModel.InsertPreloadCompleteCallback(*m_pPreloadCompleteCallback);
                }

                InitialExperiencePreLoadModelBase::~InitialExperiencePreLoadModelBase()
                {
                    m_worldAreaLoaderModel.RemovePreloadCompleteCallback(*m_pPreloadCompleteCallback);
                    Eegeo_DELETE m_pPreloadCompleteCallback;
                }

                bool InitialExperiencePreLoadModelBase::HasStarted() const
                {
                    return GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_StartedKey);
                }

                bool InitialExperiencePreLoadModelBase::HasCompleted() const
                {
                    return GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_CompletedKey);
                }

                void InitialExperiencePreLoadModelBase::PrecacheRegion()
                {
                    Eegeo_ASSERT(!HasCompleted(), "Cannot PrecacheRegion in InitialExperiencePreLoadModel step, has already completed.\n");

                    double sphereVolumeCentreLatitudeDegrees = 37.7858;
                    double sphereVolumeCentreLongitudeDegrees = -122.401;
                    double sphereVolumeRadiusMetres = 3500.0;
                    PreloadSphereVolume volume(sphereVolumeCentreLatitudeDegrees, sphereVolumeCentreLongitudeDegrees, sphereVolumeRadiusMetres);
                    m_worldAreaLoaderModel.PreloadResourcesInVolume(volume);
                }

                void InitialExperiencePreLoadModelBase::HandlePreloadComplete()
                {
                    if(!HasCompleted())
                    {
                        Complete();
                    }
                }

                void InitialExperiencePreLoadModelBase::Complete()
                {
                    Eegeo_ASSERT(!HasCompleted(), "Cannot complete InitialExperiencePreLoadModel step, has already completed.\n");
                    m_persistentSettings.SetValue(InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_CompletedKey, true);
                }

                void InitialExperiencePreLoadModelBase::PerformInitialExperience()
                {
                    Eegeo_ASSERT(!HasCompleted(), "Cannot perform InitialExperiencePreLoadModel step, has already completed.\n");
                    m_persistentSettings.SetValue(InitialExperienceModel_HasCompletedPopUpPreloadOptionExperience_StartedKey, true);
                    ShowOptions();
                }
            }
        }
    }
}
