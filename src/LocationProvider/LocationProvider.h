#pragma once

#include "ILocationProvider.h"
#include "CurrentLocationService.h"
#include "ApplicationFixedIndoorLocation.h"
#include "MapModule.h"
#include "InteriorId.h"
#include "FixedIndoorLocationService.h"

namespace ExampleApp
{
    namespace LocationProvider
    {
        class LocationProvider : public ILocationProvider {
        public:
            LocationProvider(Eegeo::Location::ILocationService& platformLocationService, Eegeo::Modules::Map::MapModule& mapModule);
            ~LocationProvider();

            void UseNativeLocationService();
            void EnableFixedLocation(const ExampleApp::ApplicationConfig::SdkModel::ApplicationFixedIndoorLocation& fixedIndoorLocation);
            void DisableFixedLocation();
            void UseIPSLocationService(Eegeo::Location::ILocationService& indoorsLocationService);

            const bool GetIsAuthorized() const;

            bool IsIndoors();
            Eegeo::Resources::Interiors::InteriorId GetInteriorId();
            bool GetLocation(Eegeo::Space::LatLong& latlong);
            bool GetAltitude(double& altitude);
            bool GetFloorIndex(int& floorIndex);
            bool GetHorizontalAccuracy(double& accuracy);
            bool GetHeadingDegrees(double& headingDegrees);
            void StopListening();
        private:
            Eegeo::Location::ILocationService& m_platformLocationService;
            Eegeo::Helpers::CurrentLocationService::CurrentLocationService *m_pCurrentLocationService;
            Eegeo::Helpers::CurrentLocationService::CurrentLocationService *m_pUnfixedLocationService;
            Eegeo::FixedLocation::FixedIndoorLocationService* m_pFixedIndoorLocationService;
        };
    }
}