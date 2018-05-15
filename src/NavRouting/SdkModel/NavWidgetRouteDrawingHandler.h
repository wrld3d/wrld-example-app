// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRoutingModel.h"
#include "NavRouteDrawingController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavWidgetRouteDrawingHandler : private Eegeo::NonCopyable
            {
            private:
                INavRoutingModel& m_navRoutingModel;
                NavRouteDrawingController& m_routeDrawingController;

                Eegeo::Helpers::TCallback1<NavWidgetRouteDrawingHandler, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_routeClearedCallback;

                void OnRouteSet(const NavRoutingRouteModel& routeModel);

                void OnRouteCleared();

            public:
                NavWidgetRouteDrawingHandler(INavRoutingModel& navRoutingModel,
                                             NavRouteDrawingController& routeDrawingController);

                ~NavWidgetRouteDrawingHandler();
            };
        }
    }
}
