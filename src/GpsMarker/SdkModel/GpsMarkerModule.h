// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModule : public Module
            {
            public:
                void Register(const TContainerBuilder& m_builder);
                void RegisterLeaves();
                void RegisterRenderableFilters();
            };
        }
    }
}