// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModel.h"
#include "LatLongAltitude.h"
#include "TerrainHeightProvider.h"
#include "MathsHelpers.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            namespace
            {
                const float SphereHeightAboveMarker = 4.5f;
                const float AnchorCyclinerHeightAboveMarker = 0.8f;
            }

            GpsMarkerModel::GpsMarkerModel(Eegeo::Location::ILocationService& locationService,
                                           Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
            : m_locationService(locationService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_hasLocation(false)
            , m_currentLocationEcef(Eegeo::dv3::Zero())
            , m_currentHeadingRadians(0)
            , m_currentHeadingVelocity(0)
            {
                
            }
            
            GpsMarkerModel::~GpsMarkerModel()
            {
                
            }
            
            bool GpsMarkerModel::UpdateGpsPosition(float dt)
            {
                Eegeo::Space::LatLong latLong(0,0);
                if(!m_locationService.GetLocation(latLong))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                float terrainHeight = 0.0f;
                Eegeo::dv3 ecefPositionFlat = latLong.ToECEF();
                
                if(m_locationService.IsIndoors())
                {
                    double altitude;
                    m_locationService.GetAltitude(altitude);
                    terrainHeight = static_cast<float>(altitude);
                }
                else if(!m_terrainHeightProvider.TryGetHeight(ecefPositionFlat, 1, terrainHeight))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                Eegeo::dv3 newLocationEcef = ecefPositionFlat + (ecefPositionFlat.Norm() * terrainHeight);
                
                float halfLife = 0.25f;
                float jumpThreshold = 50.0f;
                
                if(m_currentLocationEcef.SquareDistanceTo(newLocationEcef) < jumpThreshold * jumpThreshold)
                {
                    m_currentLocationEcef = m_currentLocationEcef.Norm() * newLocationEcef.Length();
                    m_currentLocationEcef = Eegeo::Helpers::MathsHelpers::ExpMoveTowards(m_currentLocationEcef, newLocationEcef, halfLife, dt, 0.01f);
                }
                else
                {
                    m_currentLocationEcef = newLocationEcef;
                }
                
                m_hasLocation = true;
                return true;
            }
            
            void GpsMarkerModel::UpdateHeading(float dt)
            {
                double headingDegrees = 0;
                m_locationService.GetHeadingDegrees(headingDegrees);
                headingDegrees -= 180;
                
                double headingRadians = Eegeo::Math::Deg2Rad(headingDegrees);
                
                if(headingRadians < m_currentHeadingRadians)
                {
                    float test = m_currentHeadingRadians - Eegeo::Math::kPI * 2;
                    if(Eegeo::Math::Abs(headingRadians - test) < m_currentHeadingRadians - headingRadians)
                    {
                        m_currentHeadingRadians = test;
                    }
                }
                else
                {
                    float test = m_currentHeadingRadians + Eegeo::Math::kPI * 2;
                    if(Eegeo::Math::Abs(headingRadians - test) < headingRadians - m_currentHeadingRadians)
                    {
                        m_currentHeadingRadians = test;
                    }
                }
                
                if(dt != 0)
                {
                    Eegeo::Helpers::MathsHelpers::AlphaBetaFilter(headingRadians, m_currentHeadingRadians, m_currentHeadingVelocity, m_currentHeadingRadians, m_currentHeadingVelocity, dt);
                }
            }
            
            const double GpsMarkerModel::GetSmoothedHeadingDegrees() const
            {
                double smoothedHeadingDegrees = Eegeo::Math::Rad2Deg(m_currentHeadingRadians);
                
                return smoothedHeadingDegrees;
            }
            
            int GpsMarkerModel::GetCurrentFloorIndex() const
            {
                int floorIndex = 0;
                m_locationService.GetFloorIndex(floorIndex);
                return floorIndex;
            }

            const float GpsMarkerModel::GetSphereHeightAboveMarker() const
            {
                return SphereHeightAboveMarker;
            }

            const float GpsMarkerModel::GetAnchorCyclinerHeightAboveMarker() const
            {
                return AnchorCyclinerHeightAboveMarker;
            }
        }
    }
}
