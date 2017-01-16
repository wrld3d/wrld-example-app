// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "ApplicationFixedIndoorLocation.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationFixedIndoorLocation::ApplicationFixedIndoorLocation(const Eegeo::Space::LatLong location,
                                                                           const std::string interiorId,
                                                                           const int buildingFloorIndex,
                                                                           const double orientationDegrees)
                : m_location(location)
                , m_interiorId(interiorId)
                , m_buildingFloorIndex(buildingFloorIndex)
                , m_orientationDegrees(orientationDegrees)
            {
            }

            const Eegeo::Space::LatLong& ApplicationFixedIndoorLocation::GetLocation() const
            {
                return m_location;
            }

            const Eegeo::Resources::Interiors::InteriorId& ApplicationFixedIndoorLocation::GetInteriorId() const
            {
                return m_interiorId;
            }

            const int ApplicationFixedIndoorLocation::GetBuildingFloorIndex() const
            {
                return m_buildingFloorIndex;
            }

            const double ApplicationFixedIndoorLocation::GetOrientationDegrees() const
            {
                return m_orientationDegrees;
            }
        }
    }
}
