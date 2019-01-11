// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "INavRoutingModel.h"
#include "NavRoutingLocationModel.h"
#include "IInteriorsHighlightService.h"
#include "INavRoutingHighlightsController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingHighlightsController : public INavRoutingHighlightsController, private Eegeo::NonCopyable
            {
            public:
                NavRoutingHighlightsController(INavRoutingModel& routingModel,
                                               Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService);

                ~NavRoutingHighlightsController() override {}

                void AddHighlights() override;

                void RefreshHighlights() override;

                void ClearHighlights() override;

            private:
                INavRoutingModel& m_routingModel;
                Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& m_interiorsHighlightService;

                void HighlightEntities(const NavRoutingLocationModel locationModel);
            };
        }
    }
}
