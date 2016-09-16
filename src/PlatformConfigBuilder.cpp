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
            
            platformConfig.CityThemesConfig.EmbeddedThemeManifestFile = "embedded_manifest.bin";
            platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = embeddedThemeTexturePath;
            platformConfig.CityThemesConfig.EmbeddedThemeNameContains = "Summer";
            platformConfig.CityThemesConfig.EmbeddedThemeStateName = "DayDefault";
            
            platformConfig.MapLayersConfig.Interiors.LabelsVisibleWhenExpanded = true;
            
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedFloorSpacingFactor = 0.15f;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedSelectedFloorGapFactor = 9.0f;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.FloorScaleWhenSelected = 2.0f;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedDeadZone = 0.2f;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedLookAtDeadZone = 0.2f;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.UseBoundsMaxDimension = true;
            platformConfig.MapLayersConfig.Interiors.FloorAnimatorConfiguration.UseLargeFloorGapForSmallFloorCount = false;
            
            return platformConfig;
        }
    }
}