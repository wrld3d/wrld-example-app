// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include "EnvironmentFlatteningService.h"
#include "ILocationService.h"
#include "InteriorsModel.h"

namespace Eegeo
{
    namespace FixedLocation
    {
        class FixedIndoorLocationService : public Location::ILocationService
        {
        public:
            FixedIndoorLocationService(const Space::LatLong& location,
                                       const Resources::Interiors::InteriorId& interiorId,
                                       const int floorIndex,
				                       const double headingDegrees,
                                       const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                       const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);

            const bool GetIsAuthorized() const { return true; }
            bool IsIndoors() { return true; };
            Resources::Interiors::InteriorId GetInteriorId();
            bool GetLocation(Eegeo::Space::LatLong& latlong);
            bool GetAltitude(double& altitude);
            bool GetFloorIndex(int& floorIndex);
            bool GetHorizontalAccuracy(double& accuracy);
            bool GetHeadingDegrees(double& headingDegrees);
            void StopListening();

        private:
            Resources::Interiors::InteriorId m_interiorId;
            Space::LatLong m_location;
            int m_floorIndex;
			double m_headingDegrees;
            const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
		};
    }
}
