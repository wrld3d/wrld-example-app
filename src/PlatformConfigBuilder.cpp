// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PlatformConfigBuilder.h"

namespace ExampleApp
{
    namespace PlatformConfigBuilder
    {
        Eegeo::Config::PlatformConfig Build(const Eegeo::Config::PlatformConfig& defaultPlatformConfig, const ApplicationConfig::ApplicationConfiguration& applicationConfiguration, const std::string& embeddedThemeTexturePath)
        {
            Eegeo::Config::PlatformConfig platformConfig(defaultPlatformConfig);
            
            platformConfig.OptionsConfig.InteriorsAffectedByFlattening = false;
            
            platformConfig.CoverageTreeConfig.ManifestUrl = applicationConfiguration.CoverageTreeManifestURL();
            platformConfig.CityThemesConfig.StreamedManifestUrl = applicationConfiguration.ThemeManifestURL();
            
            platformConfig.CityThemesConfig.EmbeddedThemeManifestFile = "embedded_manifest.txt";
            platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = embeddedThemeTexturePath;
            platformConfig.CityThemesConfig.EmbeddedThemeNameContains = "Summer";
            platformConfig.CityThemesConfig.EmbeddedThemeStateName = "DayDefault";
            
            platformConfig.MapLayersConfig.Interiors.LabelsVisibleWhenExpanded = true;
            
            return platformConfig;
        }
    }
}