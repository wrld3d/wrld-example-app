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
                INavRouteDrawingController& m_routeDrawingController;
                
                Eegeo::v4 m_routeColor;
                Eegeo::v4 m_routeCurrentStepColor;
                Eegeo::v4 m_routePreviousStepColor;

                Eegeo::Helpers::TCallback1<NavWidgetRouteDrawingHandler, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteDrawingHandler> m_routeClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteDrawingHandler, const int> m_currentDirectionSetCallback;

                void OnRouteSet(const NavRoutingRouteModel& routeModel);

                void OnRouteCleared();

                void OnCurrentDirectionSet(const int& directionIndex);

            public:
                NavWidgetRouteDrawingHandler(INavRoutingModel& navRoutingModel,
                                             INavRouteDrawingController& routeDrawingController);

                ~NavWidgetRouteDrawingHandler();
            };
        }
    }
}
