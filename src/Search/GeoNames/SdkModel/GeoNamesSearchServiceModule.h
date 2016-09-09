// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchServiceModule : public Module
                {
                public:
                    void Register(const TContainerBuilder& builder);
                };
            }
        }
    }
}