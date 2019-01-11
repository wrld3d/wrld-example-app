// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingHighlightsController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingHighlightsController::NavRoutingHighlightsController(INavRoutingModel& routingModel,
                                                                           Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService)
            : m_routingModel(routingModel)
            , m_interiorsHighlightService(interiorsHighlightService)
            {
            }

            void NavRoutingHighlightsController::AddHighlights()
            {
                NavRoutingLocationModel startLocation;
                if (m_routingModel.TryGetStartLocation(startLocation))
                {
                    HighlightEntities(startLocation);
                }

                NavRoutingLocationModel endLocation;
                if (m_routingModel.TryGetEndLocation(endLocation))
                {
                    HighlightEntities(endLocation);
                }
            }

            void NavRoutingHighlightsController::RefreshHighlights()
            {
                ClearHighlights();
                AddHighlights();
            }

            void NavRoutingHighlightsController::ClearHighlights()
            {
                m_interiorsHighlightService.ClearAllHighlights();
            }

            void NavRoutingHighlightsController::HighlightEntities(const NavRoutingLocationModel locationModel)
            {
                if (locationModel.GetIsIndoors())
                {
                    m_interiorsHighlightService.SetHighlights(locationModel.GetIndoorMapId().Value(), locationModel.GetEntityIds(), locationModel.GetHighlightColor());
                }
            }
        }
    }
}
