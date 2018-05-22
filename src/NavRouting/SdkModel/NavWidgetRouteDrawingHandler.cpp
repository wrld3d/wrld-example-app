// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteDrawingHandler.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavWidgetRouteDrawingHandler::NavWidgetRouteDrawingHandler(INavRoutingModel& navRoutingModel,
                                                                       TurnByTurn::INavTurnByTurnModel& navTurnByTurnModel,
                                                                       INavRouteDrawingController& routeDrawingController)
                    : m_navRoutingModel(navRoutingModel)
                    , m_navTurnByTurnModel(navTurnByTurnModel)
                    , m_routeDrawingController(routeDrawingController)
                    , m_routeColor(1, 0, 0, 0.8)
                    , m_routeCurrentStepColor(0, 1, 0, 0.8)
                    , m_routePreviousStepColor(0, 0, 1, 0.8)
                    , m_routeSetCallback(this, &NavWidgetRouteDrawingHandler::OnRouteSet)
                    , m_routeClearedCallback(this, &NavWidgetRouteDrawingHandler::OnRouteCleared)
                    , m_currentDirectionSetCallback(this, &NavWidgetRouteDrawingHandler::OnCurrentDirectionSet)
                    , m_turnByTurnUpdatedCallback(this, &NavWidgetRouteDrawingHandler::OnTurnByTurnUpdated)
            {
                m_navRoutingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_navRoutingModel.InsertRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.InsertCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_navTurnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
            }

            NavWidgetRouteDrawingHandler::~NavWidgetRouteDrawingHandler()
            {
                m_navTurnByTurnModel.RemoveUpdatedCallback(m_turnByTurnUpdatedCallback);
                m_navRoutingModel.RemoveCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_navRoutingModel.RemoveRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.RemoveRouteSetCallback(m_routeSetCallback);
            }

            void NavWidgetRouteDrawingHandler::OnRouteSet(const NavRoutingRouteModel& routeModel)
            {
                m_routeDrawingController.DrawRoute(m_routeColor);
            }

            void NavWidgetRouteDrawingHandler::OnRouteCleared()
            {
                m_routeDrawingController.ClearRoute();
            }

            void NavWidgetRouteDrawingHandler::OnCurrentDirectionSet(const int& directionIndex)
            {
                if (directionIndex > 0)
                {
                    m_routeDrawingController.SetRouteStepColor(directionIndex-1, m_routePreviousStepColor);
                }
            }
            
            void NavWidgetRouteDrawingHandler::OnTurnByTurnUpdated()
            {
                m_routeDrawingController.UpdateRouteStepProgress(m_navTurnByTurnModel.GetCurrentStepIndex(),
                                                                 m_routePreviousStepColor,
                                                                 m_routeCurrentStepColor,
                                                                 m_navTurnByTurnModel.GetIndexOfPathSegmentStartVertex(),
                                                                 m_navTurnByTurnModel.GetClosestPointOnRoute());
            }
        }
    }
}
