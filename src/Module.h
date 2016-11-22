// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"
#include "Types.h"
#include "IRenderableFilter.h"
#include "IOpenableControlViewModel.h"
#include "IScreenControlViewModel.h"
#include <vector>

namespace ExampleApp
{
    typedef std::shared_ptr<Hypodermic::ContainerBuilder> TContainerBuilder;
    typedef std::shared_ptr<Hypodermic::Container> TContainer;
    typedef std::vector<std::shared_ptr<void>> TLeaves;
    typedef std::vector<std::shared_ptr<Eegeo::Rendering::IRenderableFilter>> TRenderableFilters;
    typedef std::vector<OpenableControl::View::IOpenableControlViewModel*> TOpenableTypes;
    typedef std::vector<ScreenControl::View::IScreenControlViewModel*> TReactorTypes;
    
    class Module : private Eegeo::NonCopyable
    {
    public:
        Module()
        : m_pContainer(nullptr)
        {
        }
        
        virtual ~Module() { };
        
        virtual void Register(const TContainerBuilder& builder) = 0;
        
        // Opportunity for Modules to register any 'leaf' types, i.e. message handlers, observers, that are not dependencies of other types
        // Specifically on Android, this gives modules an opportunity to construct types with Native-affinity on the Native context.
        virtual void RegisterNativeLeaves() { };
        
        // Opportunity for Modules to register any 'leaf' types, i.e. message handlers, observers, that are not dependencies of other types, that are 'view' or 'ui' types
        // Specifically on Android, this gives modules an opportunity to construct types with UI-affinity on the UI context
        virtual void RegisterUiLeaves() { };

        // Opportunity for Modules to register any RenderableFilters
        virtual void RegisterRenderableFilters() { };
        
        // Opportunity for Modules to register any openables and/or reactors
        virtual void RegisterOpenablesAndReactors() { };
        
        template <class T>
        void RegisterLeaf()
        {
            Eegeo_ASSERT(m_pContainer != nullptr);
            auto ptr = m_pContainer->resolve<T>();
            m_leaves.push_back(ptr);
        }
        
        template <class T>
        void RegisterRenderableFilter()
        {
            Eegeo_ASSERT(m_pContainer != nullptr);
            auto ptr = m_pContainer->resolve<T>();
            m_renderableFilters.push_back(ptr);
        }
        
        void RegisterOpenable(OpenableControl::View::IOpenableControlViewModel* openable)
        {
            m_openables.push_back(openable);
        }

        void RegisterReactor(ScreenControl::View::IScreenControlViewModel* reactor)
        {
            m_reactors.push_back(reactor);
        }
        
        template <class T>
        std::shared_ptr<T> Resolve()
        {
            return m_pContainer->resolve<T>();
        }
        
        void AssignContainer(Hypodermic::Container* container)
        {
            m_pContainer = container;
        }
        
        const TLeaves& GetLeaves() const
        {
            return m_leaves;
        }
        
        const TRenderableFilters& GetRenderableFilters() const
        {
            return m_renderableFilters;
        }
        
        const TOpenableTypes& GetOpenables() const
        {
            return m_openables;
        }
        
        const TReactorTypes& GetReactors() const
        {
            return m_reactors;
        }
        
    private:
        Hypodermic::Container* m_pContainer;
        TLeaves m_leaves;
        TRenderableFilters m_renderableFilters;
        TOpenableTypes m_openables;
        TReactorTypes m_reactors;
    };
    
    typedef std::vector<std::shared_ptr<Module>> TModules;
}
