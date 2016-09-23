// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Location.h"
#include "VectorMath.h"
#include "Terrain.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModel
            {
            public:
                
                GpsMarkerModel(Eegeo::Location::ILocationService& locationService,
                               Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
                ~GpsMarkerModel();

                bool UpdateGpsPosition();
                
                bool HasLocation() const { return m_hasLocation; }
                const Eegeo::dv3& GetCurrentLocationEcef() const { return m_currentLocationEcef; }
                
                void UpdateHeading(float dt);
                const double GetSmoothedHeadingDegrees() const;
                
            private:
                
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                
                bool m_hasLocation;
                Eegeo::dv3 m_currentLocationEcef;
                
                float m_currentHeadingRadians;
                float m_currentHeadingVelocity;
            };
        }
    }
}