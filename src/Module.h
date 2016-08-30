// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"
#include "Types.h"
#include <vector>

namespace ExampleApp
{
    typedef std::shared_ptr<Hypodermic::ContainerBuilder> TContainerBuilder;
    typedef std::shared_ptr<Hypodermic::Container> TContainer;
    typedef std::vector<std::shared_ptr<void>> TLeaves;
    
    class Module : private Eegeo::NonCopyable
    {
    public:
        Module()
        : m_container(nullptr)
        {
        }
        
        virtual ~Module() { };
        
        virtual void Register(const TContainerBuilder& builder) = 0;
        virtual void RegisterLeaves() { };
        
        template <class T>
        void RegisterLeaf()
        {
            Eegeo_ASSERT(m_container != nullptr);
            std::shared_ptr<T> ptr = m_container->resolve<T>();
            m_leaves.push_back(ptr);
        }
        
        void AssignContainer(const TContainer& container)
        {
            m_container = container;
        }
        
        const TLeaves& GetLeaves() const
        {
            return m_leaves;
        }
        
    private:
        TContainer m_container;
        TLeaves m_leaves;
    };
    
    typedef std::vector<const std::shared_ptr<Module>> TModules;
}