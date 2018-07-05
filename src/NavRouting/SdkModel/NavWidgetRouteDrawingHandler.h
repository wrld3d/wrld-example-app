// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRoutingModel.h"
#include "INavTurnByTurnModel.h"
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
                TurnByTurn::INavTurnByTurnModel& m_navTurnByTurnModel;
                INavRouteDrawingController& m_routeDrawingController;
                
                Eegeo::v4 m_routeColor;
                Eegeo::v4 m_routeCurrentStepColor;
                Eegeo::v4 m_routePreviousStepColor;
                int m_currentRouteStep;

                Eegeo::Helpers::TCallback1<NavWidgetRouteDrawingHandler, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_routeClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteDrawingHandler, const int> m_currentDirectionSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_turnByTurnStartedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_turnByTurnStoppedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_turnByTurnUpdatedCallback;

                void OnRouteSet(const NavRoutingRouteModel& routeModel);

                void OnRouteCleared();

                void OnCurrentDirectionSet(const int& directionIndex);

                void OnTurnByTurnStarted();

                void OnTurnByTurnStopped();
                
                void OnTurnByTurnUpdated();

            public:
                NavWidgetRouteDrawingHandler(INavRoutingModel& navRoutingModel,
                                             TurnByTurn::INavTurnByTurnModel& navTurnByTurnModel,
                                             INavRouteDrawingController& routeDrawingController);

                ~NavWidgetRouteDrawingHandler();
            };
        }
    }
}
