#include "NavRoutingLocationFinder.h"
#include "NavRoutingLocationModel.h"
#include "ILocationService.h"
#include "IAlertBoxFactory.h"
#include "NavRouteInteriorModelHelper.h"
#include "SearchResultModel.h"
#include "NavigateToMessage.h"
#include "InteriorEntityHighlightHelpers.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingLocationFinder::NavRoutingLocationFinder(
                    Eegeo::Location::ILocationService& locationService,
                    Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                    const InteriorsExplorer::SdkModel::Highlights::IHighlightColorMapper& highlightColorMapper)
                    : m_locationService(locationService)
                    , m_interiorsModelRepository(interiorsModelRepository)
                    , m_alertBoxFactory(alertBoxFactory)
                    , m_highlightColorMapper(highlightColorMapper)
                    , m_failAlertHandler(this, &NavRoutingLocationFinder::OnFailAlertBoxDismissed)
            {

            }

            bool NavRoutingLocationFinder::TryGetCurrentLocation(NavRoutingLocationModel &outLocation)
            {
                outLocation = NavRoutingLocationModel();
                if(!m_locationService.GetIsAuthorized())
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Location service is not authorized",
                                                                 "We didn't receive authorization for location service",
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
                        outLocation = NavRoutingLocationModel("Current Location",
                                                              currentLocation,
                                                              false,
                                                              Eegeo::Resources::Interiors::InteriorId::NullId(),
                                                              0);
                        return true;
                    }
                }

                outLocation = NavRoutingLocationModel("Current Location",
                                                   currentLocation,
                                                   m_locationService.IsIndoors(),
                                                   m_locationService.GetInteriorId(),
                                                   indoorMapFloorId);
                return true;
            }

            bool NavRoutingLocationFinder::TryGetLocationFromSearchNavigationData(
                    const SearchNavigationData &searchNavigationData,
                    NavRoutingLocationModel &outLocation)
            {
                outLocation = NavRoutingLocationModel();
                NavRoutingLocationModel locationModel;

                std::vector<std::string> entityIds;
                Eegeo::v4 highlightColor;

                if(searchNavigationData.IsInterior())
                {
                    entityIds = InteriorsExplorer::SdkModel::Highlights::GetEntityIdsFromSearchResultJson(searchNavigationData.GetJsonData());
                    highlightColor = m_highlightColorMapper.GetColorsFromJson(searchNavigationData.GetJsonData()).front();

                    int indoorMapFloorId = 0;
                    const auto& indoorMapId = searchNavigationData.GetBuildingId().Value();
                    const bool interiorDetailsAvailable = NavRouteInteriorModelHelper::TryGetIndoorMapFloorId(m_interiorsModelRepository,
                                                                                                              indoorMapId,
                                                                                                              searchNavigationData.GetFloorIndex(),
                                                                                                              indoorMapFloorId);
                    if (!interiorDetailsAvailable)
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Interior not loaded",
                                                                     "Interior information is not available",
                                                                     m_failAlertHandler);
                        return false;
                    }

                    outLocation = NavRoutingLocationModel(searchNavigationData.GetTitle(),
                                                          searchNavigationData.GetLocation(),
                                                          searchNavigationData.IsInterior(),
                                                          searchNavigationData.GetBuildingId(),
                                                          indoorMapFloorId,
                                                          entityIds,
                                                          highlightColor);
                }
                else
                {
                    outLocation = NavRoutingLocationModel(searchNavigationData.GetTitle(),
                                                          searchNavigationData.GetLocation(),
                                                          searchNavigationData.IsInterior(),
                                                          searchNavigationData.GetBuildingId(),
                                                          searchNavigationData.GetFloorIndex(),
                                                          entityIds,
                                                          highlightColor);
                }
                return true;
            }

            void NavRoutingLocationFinder::OnFailAlertBoxDismissed()
            {
            }
            
            void NavRoutingLocationFinder::FailedToFindLocationMessage()
            {
                m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to acquire location",
                                                             "We couldn't find your current location",
                                                             m_failAlertHandler);
            }
        }
    }
}
