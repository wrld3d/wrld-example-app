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
                    , m_routeColor(0.f, 0.588f, 1.f, 1.0f)
                    , m_routeCurrentStepColor(0, 1.f, 0.588f, 1.0f)
                    , m_routePreviousStepColor(0.f, 0.588f, 1.f, 1.0f)
                    , m_currentRouteStep(-1)
                    , m_routeSetCallback(this, &NavWidgetRouteDrawingHandler::OnRouteSet)
                    , m_routeClearedCallback(this, &NavWidgetRouteDrawingHandler::OnRouteCleared)
                    , m_currentDirectionSetCallback(this, &NavWidgetRouteDrawingHandler::OnCurrentDirectionSet)
                    , m_turnByTurnStartedCallback(this, &NavWidgetRouteDrawingHandler::OnTurnByTurnStarted)
                    , m_turnByTurnStoppedCallback(this, &NavWidgetRouteDrawingHandler::OnTurnByTurnStopped)
                    , m_turnByTurnUpdatedCallback(this, &NavWidgetRouteDrawingHandler::OnTurnByTurnUpdated)
            {
                m_navRoutingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_navRoutingModel.InsertRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.InsertCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_navTurnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                m_navTurnByTurnModel.InsertStoppedCallback(m_turnByTurnStoppedCallback);
                m_navTurnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
            }

            NavWidgetRouteDrawingHandler::~NavWidgetRouteDrawingHandler()
            {
                m_navTurnByTurnModel.RemoveUpdatedCallback(m_turnByTurnUpdatedCallback);
                m_navTurnByTurnModel.RemoveStoppedCallback(m_turnByTurnStoppedCallback);
                m_navTurnByTurnModel.RemoveStartedCallback(m_turnByTurnStartedCallback);
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
                if (m_currentRouteStep != -1 && directionIndex != m_currentRouteStep)
                {
                    m_routeDrawingController.SetRouteStepColor(m_currentRouteStep, m_routePreviousStepColor);
                }

                m_currentRouteStep = directionIndex;
            }

            void NavWidgetRouteDrawingHandler::OnTurnByTurnStarted()
            {
                m_currentRouteStep = m_navTurnByTurnModel.GetCurrentStepIndex();
            }

            void NavWidgetRouteDrawingHandler::OnTurnByTurnStopped()
            {
                Eegeo_ASSERT(m_currentRouteStep >= 0, "Invalid route step index");
                m_routeDrawingController.SetRouteStepColor(m_currentRouteStep, m_routePreviousStepColor);
                m_currentRouteStep = -1;
            }
            
            void NavWidgetRouteDrawingHandler::OnTurnByTurnUpdated()
            {
                if (m_currentRouteStep >= 0)
                {
                    m_routeDrawingController.UpdateRouteStepProgress(m_currentRouteStep,
                                                                     m_routePreviousStepColor,
                                                                     m_routeCurrentStepColor,
                                                                     m_navTurnByTurnModel.GetIndexOfPathSegmentStartVertex(),
                                                                     m_navTurnByTurnModel.GetClosestPointOnRoute());
                }
            }
        }
    }
}
