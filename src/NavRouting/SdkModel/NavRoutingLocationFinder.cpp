#include "NavRoutingLocationFinder.h"
#include "NavRoutingLocationModel.h"
#include "ILocationService.h"
#include "IAlertBoxFactory.h"
#include "NavRouteInteriorModelHelper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingLocationFinder::NavRoutingLocationFinder(
                    Eegeo::Location::ILocationService& locationService,
                    Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
                    : m_locationService(locationService)
                    , m_interiorsModelRepository(interiorsModelRepository)
                    , m_alertBoxFactory(alertBoxFactory)
                    , m_failAlertHandler(this, &NavRoutingLocationFinder::OnFailAlertBoxDismissed)
            {

            }

            bool NavRoutingLocationFinder::TryGetCurrentLocation(NavRoutingLocationModel &outLocation)
            {
                outLocation = NavRoutingLocationModel();
                if(!m_locationService.GetIsAuthorized())
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Location service is not authorized",
                                                                 "We didn't recieve autorization for location service",
                                                                 m_failAlertHandler);
                    return false;
                }

                Eegeo::Space::LatLong currentLocation = Eegeo::Space::LatLong(0,0);

                bool locationServiceHasUserLocation = m_locationService.GetLocation(currentLocation);
                if(!locationServiceHasUserLocation)
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to acquire location",
                                                                 "We couldn't find your current location",
                                                                 m_failAlertHandler);
                    return false;
                }

                int floorIndex = 0;
                m_locationService.GetFloorIndex(floorIndex);

                int indoorMapFloorId = 0;

                if (m_locationService.IsIndoors())
                {
                    const auto& indoorMapId = m_locationService.GetInteriorId().Value();
                    const bool interiorDetailsAvailable = NavRouteInteriorModelHelper::TryGetIndoorMapFloorId(m_interiorsModelRepository,
                                                                                                              indoorMapId,
                                                                                                              floorIndex,
                                                                                                              indoorMapFloorId);
                    if (!interiorDetailsAvailable)
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Interior not loaded",
                                                                     "Interior information is not available",
                                                                     m_failAlertHandler);
                        return false;
                    }
                }

                outLocation = NavRoutingLocationModel("Current Location",
                                                   currentLocation,
                                                   m_locationService.IsIndoors(),
                                                   m_locationService.GetInteriorId(),
                                                   indoorMapFloorId);
                return true;
            }

            bool NavRoutingLocationFinder::TryGetLocationFromSearchResultModel(
                    const Search::SdkModel::SearchResultModel& searchResultModel,
                    NavRoutingLocationModel &outLocation)
            {
                outLocation = NavRoutingLocationModel();
                NavRoutingLocationModel locationModel;
                if(searchResultModel.IsInterior())
                {
                    int indoorMapFloorId = 0;
                    const auto& indoorMapId = searchResultModel.GetBuildingId().Value();
                    const bool interiorDetailsAvailable = NavRouteInteriorModelHelper::TryGetIndoorMapFloorId(m_interiorsModelRepository,
                                                                                                              indoorMapId,
                                                                                                              searchResultModel.GetFloor(),
                                                                                                              indoorMapFloorId);
                    if (!interiorDetailsAvailable)
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Interior not loaded",
                                                                     "Interior information is not available",
                                                                     m_failAlertHandler);
                        return false;
                    }

                    outLocation = NavRoutingLocationModel(searchResultModel.GetTitle(),
                                                          searchResultModel.GetLocation(),
                                                          searchResultModel.IsInterior(),
                                                          searchResultModel.GetBuildingId(),
                                                          indoorMapFloorId);
                }
                else
                {
                    outLocation = NavRoutingLocationModel(searchResultModel.GetTitle(),
                                                          searchResultModel.GetLocation(),
                                                          searchResultModel.IsInterior(),
                                                          searchResultModel.GetBuildingId(),
                                                          searchResultModel.GetFloor());
                }
                return true;
            }

            void NavRoutingLocationFinder::OnFailAlertBoxDismissed()
            {
            }
        }
    }
}