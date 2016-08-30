// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"
#include <vector>

namespace ExampleApp
{
    class IModule
    {
    public:
        virtual ~IModule() { };
        
        virtual void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder) = 0;
    };
    
    typedef std::vector<const std::shared_ptr<IModule>> TModules;
}