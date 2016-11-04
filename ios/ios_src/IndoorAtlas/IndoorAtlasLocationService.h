// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "InteriorsModel.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        class IndoorAtlasLocationService : public Eegeo::Location::ILocationService
        {
        public:
            IndoorAtlasLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                       const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                       const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
            
            const bool GetIsAuthorized() const;
            
            bool IsIndoors();
            bool GetIndoorID(int& indoorID);
            bool GetLocation(Eegeo::Space::LatLong& latLong);
            bool GetAltitude(double& altitude);
            bool GetFloorIndex(int& floorIndex);
            bool GetHorizontalAccuracy(double& accuracy);
            bool GetHeadingDegrees(double& headingDegrees);
            void StopListening();
            
            void SetLocation(Eegeo::Space::LatLong& latLong);
            void SetFloorIndex(int floorIndex);
            
        private:
            Eegeo::Location::ILocationService& m_defaultLocationService;
            const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            
            Eegeo::Space::LatLong m_latLong;
            int m_floorIndex;
        };
    }
}