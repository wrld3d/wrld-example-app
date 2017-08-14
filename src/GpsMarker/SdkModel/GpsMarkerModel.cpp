// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModel.h"
#include "LatLongAltitude.h"
#include "TerrainHeightProvider.h"
#include "MathsHelpers.h"
#include "PointOnMapBuilder.h"
#include "CoordinateConversion.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModel::GpsMarkerModel(Eegeo::Location::ILocationService& locationService,
                                           Eegeo::BlueSphere::BlueSphereModel& blueSphereModel)
            : m_locationService(locationService)
            , m_currentLocationEcef(Eegeo::dv3::Zero())
            , m_currentHeadingRadians(0)
            , m_currentHeadingVelocity(0)
            , m_blueSphereModel(blueSphereModel)
            {
                m_blueSphereModel.SetEnabled(true);
            }
            
            GpsMarkerModel::~GpsMarkerModel()
            {
                
            }
            
            bool GpsMarkerModel::UpdateGpsPosition(float dt)
            {
                Eegeo::Space::LatLong locationServiceLatLong(0,0);
                if(!m_locationService.GetLocation(locationServiceLatLong))
                {
                    return false;
                }
                
                float terrainHeight = 0.0f;
                Eegeo::dv3 ecefPositionFlat = locationServiceLatLong.ToECEF();
                
                if(m_locationService.IsIndoors())
                {
                    double altitude;
                    m_locationService.GetAltitude(altitude);
                    terrainHeight = static_cast<float>(altitude);
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
                
                Eegeo::Space::LatLong coord = Eegeo::Space::LatLong::FromECEF(m_currentLocationEcef);
                int floorIndex;
                m_locationService.GetFloorIndex(floorIndex);
                const Eegeo::Resources::Interiors::InteriorId& interiorId = m_locationService.GetInteriorId();
                
                m_blueSphereModel.SetCoordinate(coord);
                m_blueSphereModel.SetIndoorMap(interiorId.Value(), floorIndex);

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
                
                m_blueSphereModel.SetHeadingRadians(m_currentHeadingRadians);
            }
            
            void GpsMarkerModel::SetEnabled(bool enabled)
            {
                m_blueSphereModel.SetEnabled(enabled);
            }

            const float GpsMarkerModel::GetSphereHeightAboveBase() const
            {
                return m_blueSphereModel.GetSphereHeightAboveBase();
            }

            bool GpsMarkerModel::IsLocationIndoors() const
            {
                return m_blueSphereModel.IsLocationIndoors();
            }
        }
    }
}
