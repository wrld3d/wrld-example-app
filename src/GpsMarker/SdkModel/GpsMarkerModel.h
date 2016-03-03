// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Location.h"
#include "VectorMath.h"
#include "Terrain.h"
#include "Interiors.h"
#include "Rendering.h"

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
                               Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                               const bool interiorsAffectedByFlattening);
                ~GpsMarkerModel();

                bool UpdateGpsPosition();
                
                bool HasLocation() const { return m_hasLocation; }
                const Eegeo::dv3& GetCurrentLocationEcef() const { return m_currentLocationEcef; }
                
                void GetFinalEcefPosition(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlattening,
                                          Eegeo::dv3& out_position);
                
            private:
                
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
                bool m_hasLocation;
                Eegeo::dv3 m_currentLocationEcef;
                const bool m_interiorsAffectedByFlattening;
            };
        }
    }
}