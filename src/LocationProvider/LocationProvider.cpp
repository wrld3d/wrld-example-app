#include "LocationProvider.h"
#include "FixedIndoorLocationService.h"
#include "InteriorsPresentationModule.h"

namespace ExampleApp
{
    namespace LocationProvider
    {
        LocationProvider::LocationProvider(Eegeo::Location::ILocationService& platformLocationService, Eegeo::Modules::Map::MapModule& mapModule)
                : m_platformLocationService(platformLocationService)
                , m_pUnfixedLocationService(NULL)
                , m_pFixedIndoorLocationService(NULL)
                , m_pCurrentLocationService(NULL)
        {
            m_pUnfixedLocationService = Eegeo_NEW(Eegeo::Helpers::CurrentLocationService::CurrentLocationService)(m_platformLocationService);
            m_pFixedIndoorLocationService = Eegeo_NEW(Eegeo::FixedLocation::FixedIndoorLocationService)(
                    mapModule.GetEnvironmentFlatteningService(),
                    mapModule.GetInteriorsPresentationModule().GetInteriorInteractionModel());
            // Cast here to avoid copy constructor
            m_pCurrentLocationService = Eegeo_NEW(Eegeo::Helpers::CurrentLocationService::CurrentLocationService)(*static_cast<Eegeo::Location::ILocationService*>(m_pUnfixedLocationService));
        }

        LocationProvider::~LocationProvider()
        {
            Eegeo_DELETE(m_pCurrentLocationService);
            Eegeo_DELETE(m_pFixedIndoorLocationService);
            Eegeo_DELETE(m_pUnfixedLocationService);
        }

        void LocationProvider::UseNativeLocationService()
        {
            m_pUnfixedLocationService->SetLocationService(m_platformLocationService);
        }

        void LocationProvider::EnableFixedLocation(const ExampleApp::ApplicationConfig::SdkModel::ApplicationFixedIndoorLocation& fixedIndoorLocation)
        {
            m_pFixedIndoorLocationService->SetFixedLocation(fixedIndoorLocation.GetLocation(),
                                                            fixedIndoorLocation.GetInteriorId(),
                                                            fixedIndoorLocation.GetBuildingFloorIndex(),
                                                            fixedIndoorLocation.GetOrientationDegrees());
            m_pCurrentLocationService->SetLocationService(*m_pFixedIndoorLocationService);
        }

        void LocationProvider::DisableFixedLocation()
        {
            m_pCurrentLocationService->SetLocationService(*m_pUnfixedLocationService);
        }

        void LocationProvider::UseIPSLocationService(Eegeo::Location::ILocationService& indoorsLocationService)
        {
            m_pUnfixedLocationService->SetLocationService(indoorsLocationService);
        }

        const bool LocationProvider::GetIsAuthorized() const
        {
            return m_pCurrentLocationService->GetIsAuthorized();
        }

        bool LocationProvider::IsIndoors()
        {
            return m_pCurrentLocationService->IsIndoors();
        }

        Eegeo::Resources::Interiors::InteriorId LocationProvider::GetInteriorId()
        {
            return m_pCurrentLocationService->GetInteriorId();
        }

        bool LocationProvider::GetLocation(Eegeo::Space::LatLong& latlong)
        {
            return m_pCurrentLocationService->GetLocation(latlong);
        }

        bool LocationProvider::GetAltitude(double& altitude)
        {
            return m_pCurrentLocationService->GetAltitude(altitude);
        }

        bool LocationProvider::GetFloorIndex(int &floorIndex)
        {
            return m_pCurrentLocationService->GetFloorIndex(floorIndex);
        }

        bool LocationProvider::GetHorizontalAccuracy(double& accuracy)
        {
            return m_pCurrentLocationService->GetHorizontalAccuracy(accuracy);
        }

        bool LocationProvider::GetHeadingDegrees(double& headingDegrees)
        {
            return m_pCurrentLocationService->GetHeadingDegrees(headingDegrees);
        }

        void LocationProvider::StopListening()
        {
            m_pCurrentLocationService->StopListening();
        }
    }
}
