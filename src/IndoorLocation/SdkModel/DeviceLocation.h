// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace IndoorLocation
    {
        namespace SdkModel
        {
            struct DeviceLocation : private Eegeo::NonCopyable
            {
            public:
                
                DeviceLocation()
                : m_building("")
                , m_floor(0)
                , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
                , m_mapX(0.0f)
                , m_mapY(0.0f)
                ,isBlueToothEnabled(false)
                {
                }
                
                void Update(float mapX, float mapY, double latitudeDegrees, double longitudeDegrees, const Eegeo::Resources::Interiors::InteriorId& building, int floor)
                {
                    m_latLong.SetLatitude(Eegeo::Math::Deg2Rad(latitudeDegrees));
                    m_latLong.SetLongitude(Eegeo::Math::Deg2Rad(longitudeDegrees));
                    m_mapX = mapX;
                    m_mapY = mapY;
                    m_building = building;
                    m_floor = floor;
                }
                
                const Eegeo::Resources::Interiors::InteriorId& GetBuildingID() const { return m_building; }
                int GetFloor() const { return m_floor; }
                const Eegeo::Space::LatLong& GetLatLong() const { return m_latLong; }
                const float GetMapX() const { return m_mapX; }
                const float GetMapY() const { return m_mapY; }
                const float GetHeading() const { return m_heading; }
                const bool GetBlueToothState() const{return isBlueToothEnabled;}
                void SetBlueToothState(bool blueToothStatus){isBlueToothEnabled = blueToothStatus;}
                void setHeading(double heading) { m_heading = heading;}
                
            private:
                Eegeo::Resources::Interiors::InteriorId m_building;
                int m_floor;
                Eegeo::Space::LatLong m_latLong;
                float m_mapX;
                float m_mapY;
                double m_heading = 0; // Heading from senion lab. Updated by senion lab heading callback
                bool isBlueToothEnabled;
            };
        }
    }
}