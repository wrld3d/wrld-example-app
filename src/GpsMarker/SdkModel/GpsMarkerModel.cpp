// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModel.h"
#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "TerrainHeightProvider.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModel::GpsMarkerModel(const std::shared_ptr<Eegeo::Location::ILocationService>& locationService,
                                           const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>& terrainHeightProvider)
            : m_locationService(locationService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_hasLocation(false)
            , m_currentLocationEcef(Eegeo::dv3::Zero())
            {
                
            }
            
            GpsMarkerModel::~GpsMarkerModel()
            {
                
            }
            
            bool GpsMarkerModel::UpdateGpsPosition()
            {
                Eegeo::Space::LatLong latLong(0,0);
                if(!m_locationService->GetLocation(latLong))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                float terrainHeight;
                Eegeo::dv3 ecefPositionFlat = latLong.ToECEF();
                if(!m_terrainHeightProvider->TryGetHeight(ecefPositionFlat, 1, terrainHeight))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                m_currentLocationEcef = ecefPositionFlat + (ecefPositionFlat.Norm() * terrainHeight);
                m_hasLocation = true;
                return true;
            }
        }
    }
}