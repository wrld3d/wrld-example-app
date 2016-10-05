// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

namespace ExampleApp
{
    class MobileExampleApp;
}

#include "Types.h"
#include "Hypodermic/ContainerBuilder.h"
#include "ICallback.h"
#include "Module.h"

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

        void RegisterModuleInstance(const std::shared_ptr<Module> module);
        void RegisterDefaultModules();
        
        void ApplyModuleRegistrations();
        void BuildContainer();
        void ResolveModules();
        void ResolveNativeLeaves();
        void ResolveUiLeaves();
        
        const std::shared_ptr<MobileExampleApp> BuildMobileExampleApp();
        const TContainer& GetContainer() const;
        
        template <class T>
        std::shared_ptr< T > Resolve()
        {
            return m_appContainer->resolve<T>();
        }
        
        template <class T>
		std::shared_ptr< T > ResolveLeaf()
		{
			auto ptr = m_appContainer->resolve<T>();
			m_leaves.push_back(ptr);
			return ptr;
		}

    private:

        const std::shared_ptr<Hypodermic::ContainerBuilder> m_moduleContainerBuilder;
        std::shared_ptr<Hypodermic::Container> m_moduleContainer;

        const std::shared_ptr<Hypodermic::ContainerBuilder> m_appContainerBuilder;
        std::shared_ptr<Hypodermic::Container> m_appContainer;
        
        TLeaves m_leaves;
        
        Eegeo::Helpers::CallbackCollection1<TModules&> m_moduleRegistrationCallbacks;
    };
}
