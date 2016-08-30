// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchServiceModule
                {
                public:
                    EegeoSearchServiceModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
                    
                    void Register();
                private:
                    const std::shared_ptr<Hypodermic::ContainerBuilder> m_builder;
                };
            }
        }
    }
}