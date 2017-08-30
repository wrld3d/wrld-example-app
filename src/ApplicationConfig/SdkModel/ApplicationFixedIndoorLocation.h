// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationFixedIndoorLocation {
            public:
                ApplicationFixedIndoorLocation(const Eegeo::Space::LatLong location,
                                               const std::string interiorId,
                                               const int buildingFloorIndex,
                                               const double orientationDegrees,
                                               const double locationDistance);

                const Eegeo::Space::LatLong& GetLocation() const;
                const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const;
                const int GetBuildingFloorIndex() const;
                const double GetOrientationDegrees() const;
                const double GetLocationDistance() const;

            private:
                const Eegeo::Space::LatLong m_location;
                const Eegeo::Resources::Interiors::InteriorId m_interiorId;
                const int m_buildingFloorIndex;
                const double m_orientationDegrees;
                const double m_locationDistance;
            };
        }
    }
}
