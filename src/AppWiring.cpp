// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "AppWiring.h"
#include "WorldModule.h"
#include "AppModule.h"
#include "LoadingScreenModule.h"
#include "NetworkModule.h"
#include "AppCameraModule.h"
#include "ToursModule.h"
#include "InteriorsExplorerModule.h"
#include "MyPinCreationModule.h"
#include "VisualMapModule.h"
#include "WorldAreaLoaderModule.h"
#include "IInitialExperienceModule.h"
#include "IWorldAreaLoaderModel.h"
#include "WorldPinsModule.h"
#include "InteriorsEntitiesPinsModule.h"
#include "PoiRingModule.h"
#include "WatermarkModule.h"
#include "ViewControllerUpdaterModule.h"

namespace ExampleApp
{
    AppWiring::AppWiring()
    : m_moduleContainerBuilder(std::make_shared<Hypodermic::ContainerBuilder>())
    , m_appContainerBuilder(std::make_shared<Hypodermic::ContainerBuilder>())
    {
        m_moduleContainerBuilder->registerType<TModules>().singleInstance();
        m_moduleContainer = m_moduleContainerBuilder->build();
    }
    
    AppWiring::~AppWiring()
    {
    }
    
    void AppWiring::RegisterModuleInstance(const std::shared_ptr<Module> module)
    {
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        moduleSet->push_back(module);
    }

    void AppWiring::RegisterDefaultModules()
    {
        RegisterModule<WorldModule>();
        RegisterModule<LoadingScreenModule>();
        RegisterModule<AppModule>();
        RegisterModule<Net::SdkModel::NetworkModule>();
        RegisterModule<AppCamera::SdkModel::AppCameraModule>();
        RegisterModule<Tours::ToursModule>();
        RegisterModule<InteriorsExplorer::SdkModel::InteriorsExplorerModule>();
        RegisterModule<MyPinCreation::SdkModel::MyPinCreationModule>();
        RegisterModule<VisualMap::SdkModel::VisualMapModule>();
        RegisterModule<WorldAreaLoader::SdkModel::WorldAreaLoaderModule>();
        RegisterModule<WorldPins::SdkModel::WorldPinsModule>();
        RegisterModule<InteriorsEntitiesPins::SdkModel::InteriorsEntitiesPinsModule>();
        RegisterModule<MyPinCreation::PoiRing::SdkModel::PoiRingModule>();
        RegisterModule<Watermark::SdkModel::WatermarkModule>();
        RegisterModule<ViewControllerUpdater::View::ViewControllerUpdaterModule>();
        
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        m_moduleRegistrationCallbacks.ExecuteCallbacks(*moduleSet);
    }
    
    void AppWiring::ResolveModules()
    {
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        for (auto module : *moduleSet)
        {
            module->Register(m_appContainerBuilder);
        }
        m_appContainer = m_appContainerBuilder->build();
        for (auto module : *moduleSet)
        {
            module->AssignContainer(m_appContainer);
            module->RegisterLeaves();
            for (auto leaf : module->GetLeaves())
            {
                m_leaves.push_back(leaf);
            }
        }
    }
    
    const std::shared_ptr<MobileExampleApp> AppWiring::BuildMobileExampleApp()
    {
        Eegeo_ASSERT(m_appContainer != nullptr, "Call ResolveModules before BuildMobileExampleApp");
        auto initialExperience = m_appContainer->resolve<InitialExperience::SdkModel::IInitialExperienceModule>();
        initialExperience->InitialiseWithApplicationModels(*m_appContainer->resolve<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>());
        return m_appContainer->resolve<MobileExampleApp>();
    }
    
    void AppWiring::RegisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback)
    {
        m_moduleRegistrationCallbacks.AddCallback(callback);
    }
    
    void AppWiring::UnregisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback)
    {
        m_moduleRegistrationCallbacks.RemoveCallback(callback);
    }
}