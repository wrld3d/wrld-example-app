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

            // General
            void OnPause() override;
            void OnResume() override;
            
            // Location
            bool IsLocationAuthorized() const override;
            bool IsLocationActive() const override;
            bool GetLocation(Eegeo::Space::LatLong& latlong) const override;
            bool GetAltitude(double& altitude) const override;
            bool GetHorizontalAccuracy(double& accuracy) const override;
            
            void StartUpdatingLocation() override;
            void StopUpdatingLocation() override;
            
            // Heading
            bool GetHeadingDegrees(double& headingDegrees) const override;
            bool IsHeadingAuthorized() const override;
            bool IsHeadingActive() const override;
            
            void StartUpdatingHeading() override;
            void StopUpdatingHeading() override;
            
            // Indoor
            bool IsIndoors() const override;
            Resources::Interiors::InteriorId GetInteriorId() const override;
            bool GetFloorIndex(int& floorIndex) const override;
            bool IsIndoorAuthorized() const override;

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
