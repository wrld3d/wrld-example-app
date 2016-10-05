// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <Module.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewModule: public Module
            {
            public:
            	void Register(const TContainerBuilder& builder);
            	void RegisterLeaves();
            };
        }
    }
}
