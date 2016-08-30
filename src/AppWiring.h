// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"
#include "Hypodermic/ContainerBuilder.h"
#include "MobileExampleApp.h"
#include "ICallback.h"
#include "IModule.h"

namespace ExampleApp
{
    class AppWiring : private Eegeo::NonCopyable
    {
    public:
        AppWiring();
        ~AppWiring();
        
        void RegisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback);
        void UnregisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback);
        
        template <typename T>
        void RegisterModule()
        {
            auto moduleSet = m_moduleContainer->resolve<TModules>();
            moduleSet->push_back(std::make_shared<T>());
        }
        
        void RegisterModuleInstance(const std::shared_ptr<IModule> module);
        void RegisterDefaultModules();
        void ResolveModules();
        
        const std::shared_ptr<MobileExampleApp> BuildMobileExampleApp();

        template <class T>
        std::shared_ptr< T > Resolve()
        {
            return m_appContainer->resolve<T>();
        }
        
    private:
        const std::shared_ptr<Hypodermic::ContainerBuilder> m_moduleContainerBuilder;
        std::shared_ptr<Hypodermic::Container> m_moduleContainer;

        const std::shared_ptr<Hypodermic::ContainerBuilder> m_appContainerBuilder;
        std::shared_ptr<Hypodermic::Container> m_appContainer;
        
        Eegeo::Helpers::CallbackCollection1<TModules&> m_moduleRegistrationCallbacks;
    };
}