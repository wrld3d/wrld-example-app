// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteDrawingHandler.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavWidgetRouteDrawingHandler::NavWidgetRouteDrawingHandler(INavRoutingModel& navRoutingModel,
                                                                       INavRouteDrawingController& routeDrawingController)
                    : m_navRoutingModel(navRoutingModel)
                    , m_routeDrawingController(routeDrawingController)
                    , m_routeSetCallback(this, &NavWidgetRouteDrawingHandler::OnRouteSet)
                    , m_routeClearedCallback(this, &NavWidgetRouteDrawingHandler::OnRouteCleared)
            {
                m_navRoutingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_navRoutingModel.InsertRouteClearedCallback(m_routeClearedCallback);
            }

            NavWidgetRouteDrawingHandler::~NavWidgetRouteDrawingHandler()
            {
                m_navRoutingModel.RemoveRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.RemoveRouteSetCallback(m_routeSetCallback);
            }

            void NavWidgetRouteDrawingHandler::OnRouteSet(const NavRoutingRouteModel& routeModel)
            {
                m_routeDrawingController.AddRoute(routeModel.GetDirections(), Eegeo::v4(1, 0, 0, 0.8));
            }

            void NavWidgetRouteDrawingHandler::OnRouteCleared()
            {
                m_routeDrawingController.ClearRoute();
            }
        }
    }
}
