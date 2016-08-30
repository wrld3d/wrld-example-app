// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "GlHelpers.h"
#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModule
            {
            public:
                ~GpsMarkerModule();
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& m_builder);
            private:
                Eegeo::Helpers::GLHelpers::TextureInfo m_gpsIconTexture;
            };
        }
    }
}