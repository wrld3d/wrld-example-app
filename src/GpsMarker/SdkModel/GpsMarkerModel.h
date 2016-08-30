// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Location.h"
#include "VectorMath.h"
#include "Terrain.h"

#include <memory>

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModel
            {
            public:
                
                GpsMarkerModel(const std::shared_ptr<Eegeo::Location::ILocationService>& locationService,
                               const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>& terrainHeightProvider);
                ~GpsMarkerModel();

                bool UpdateGpsPosition();
                
                bool HasLocation() const { return m_hasLocation; }
                const Eegeo::dv3& GetCurrentLocationEcef() const { return m_currentLocationEcef; }
                
            private:
                
                std::shared_ptr<Eegeo::Location::ILocationService> m_locationService;
                std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider> m_terrainHeightProvider;
                
                bool m_hasLocation;
                Eegeo::dv3 m_currentLocationEcef;
            };
        }
    }
}