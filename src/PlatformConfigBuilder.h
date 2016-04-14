// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "PlatformConfig.h"
#include "ApplicationConfiguration.h"
#include <string>

namespace ExampleApp
{
    namespace PlatformConfigBuilder
    {
        Eegeo::Config::PlatformConfig Build(const Eegeo::Config::PlatformConfig& defaultPlatformConfig, const ApplicationConfig::ApplicationConfiguration& applicationConfiguration, const std::string& embeddedThemeTexturePath);
    }
}