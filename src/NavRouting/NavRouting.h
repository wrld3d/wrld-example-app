// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "RouteData.h"
#include "PolylineShapeArgs.h"

#include <vector>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            enum NavRoutingMode
            {
                NotReady = 0,
                Ready,
                Active,
            };

            struct NavRouteDrawingVertexData;

            class INavRoutingModel;
            class NavRoutingModule;
            class INavRoutingPolylineFactory;
            class INavRouteDrawingController;
            class INavRoutingServiceController;
            class NavWidgetRouteUpdateHandler;
            class NavWidgetRouteDrawingHandler;
            class NavRoutingController;
            class NavRoutingCameraController;

            typedef Eegeo::Shapes::Polylines::PolylineShapeArgs PolyLineArgs;
            typedef std::vector<PolyLineArgs::ShapeModel::IdType> RouteLines;
            typedef Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Routes::Webservice::RouteData>> RoutesReceivedCallback;
            typedef Eegeo::Helpers::ICallback0 RouteFailedCallback;

            namespace TurnByTurn
            {
                class INavTurnByTurnModel;
                class NavTurnByTurnController;
            }

        }

        namespace View
        {
            class INavWidgetView;
            class INavWidgetViewModel;
            class NavUIModule;
            class NavWidgetController;
            class NavWidgetOpenableControl;
            class NavWidgetViewModel;
        }
    }
}
