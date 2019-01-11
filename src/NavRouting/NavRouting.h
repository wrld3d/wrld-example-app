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
            class NavRoutingRouteModel;
            class NavRoutingLocationModel;
            class NavRoutingDirectionModel;
            class INavRoutingPolylineFactory;
            class INavRouteDrawingController;
            class INavRoutingHighlightsController;
            class INavRoutingLocationFinder;
            class INavRoutingServiceController;
            class NavWidgetRouteUpdateHandler;
            class NavWidgetRouteDrawingHandler;
            class NavRoutingController;
            class NavRoutingCameraController;
            class INavRoutingCustomLocationPicker;

            typedef Eegeo::Shapes::Polylines::PolylineShapeArgs PolyLineArgs;
            typedef std::vector<PolyLineArgs::ShapeModel::IdType> RouteLines;
            typedef Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Routes::Webservice::RouteData>> RoutesReceivedCallback;
            typedef Eegeo::Helpers::ICallback0 RouteFailedCallback;

            namespace TurnByTurn
            {
                class INavTurnByTurnModel;
                class NavTurnByTurnController;
                class NavTurnByTurnCompletionHandler;
            }

            namespace InstructionTokens
            {
                static const char* Distance = "<dist>";
                static const char* FloorName = "<floor>";
                static const char* NextFloorName = "<nextfloor>";
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
