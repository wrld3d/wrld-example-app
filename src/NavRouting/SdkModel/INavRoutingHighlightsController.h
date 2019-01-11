// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "INavRoutingModel.h"
#include "NavRoutingLocationModel.h"
#include "IInteriorsHighlightService.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingHighlightsController
            {
            public:
                virtual ~INavRoutingHighlightsController() {}

                virtual void AddHighlights() = 0;

                virtual void RefreshHighlights() = 0;

                virtual void ClearHighlights() = 0;
            };
        }
    }
}
