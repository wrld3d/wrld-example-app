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
                    , m_routeColor(1, 0, 0, 0.8)
                    , m_routeCurrentStepColor(0, 1, 0, 0.8)
                    , m_routePreviousStepColor(0, 0, 1, 0.8)
                    , m_routeSetCallback(this, &NavWidgetRouteDrawingHandler::OnRouteSet)
                    , m_routeClearedCallback(this, &NavWidgetRouteDrawingHandler::OnRouteCleared)
                    , m_currentDirectionSetCallback(this, &NavWidgetRouteDrawingHandler::OnCurrentDirectionSet)
            {
                m_navRoutingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_navRoutingModel.InsertRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.InsertCurrentDirectionSetCallback(m_currentDirectionSetCallback);
            }

            NavWidgetRouteDrawingHandler::~NavWidgetRouteDrawingHandler()
            {
                m_navRoutingModel.RemoveCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_navRoutingModel.RemoveRouteClearedCallback(m_routeClearedCallback);
                m_navRoutingModel.RemoveRouteSetCallback(m_routeSetCallback);
            }

            void NavWidgetRouteDrawingHandler::OnRouteSet(const NavRoutingRouteModel& routeModel)
            {
                m_routeDrawingController.AddRoute(routeModel.GetDirections(), m_routeColor);
            }

            void NavWidgetRouteDrawingHandler::OnRouteCleared()
            {
                m_routeDrawingController.ClearRoute();
            }

            void NavWidgetRouteDrawingHandler::OnCurrentDirectionSet(const int& directionIndex)
            {
                m_routeDrawingController.SetRouteColor(directionIndex, m_routeCurrentStepColor);
                
                if(directionIndex > 0)
                {
                    int previousIndex = directionIndex-1;
                    while (previousIndex >= 0)
                    {
                        m_routeDrawingController.SetRouteColor(previousIndex, m_routePreviousStepColor);
                        previousIndex--;
                    }
                }
            }
        }
    }
}
