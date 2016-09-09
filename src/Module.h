// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"
#include "Types.h"
#include "IRenderableFilter.h"
#include <vector>

namespace ExampleApp
{
    typedef std::shared_ptr<Hypodermic::ContainerBuilder> TContainerBuilder;
    typedef std::shared_ptr<Hypodermic::Container> TContainer;
    typedef std::vector<std::shared_ptr<void>> TLeaves;
    typedef std::vector<std::shared_ptr<Eegeo::Rendering::IRenderableFilter>> TRenderableFilters;
    
    class Module : private Eegeo::NonCopyable
    {
    public:
        Module()
        : m_pContainer(nullptr)
        {
        }
        
        virtual ~Module() { };
        
        virtual void Register(const TContainerBuilder& builder) = 0;
        virtual void RegisterLeaves() { };
        virtual void RegisterRenderableFilters() { };
        
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
        
    private:
        Hypodermic::Container* m_pContainer;
        TLeaves m_leaves;
        TRenderableFilters m_renderableFilters;
    };
    
    typedef std::vector<const std::shared_ptr<Module>> TModules;
}