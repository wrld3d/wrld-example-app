// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "Location.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {

                class NavTurnByTurnController
                {
                public:

                    NavTurnByTurnController(INavTurnByTurnModel& turnByTurnModel,
                                            INavRoutingModel& navRoutingModel,
                                            Eegeo::Location::NavigationService& navigationService);
                    ~NavTurnByTurnController();

                    void Update(float dt);

                private:

                    INavTurnByTurnModel& m_turnByTurnModel;
                    INavRoutingModel& m_navRoutingModel;
                    Eegeo::Location::NavigationService& m_navigationService;

                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnStartedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnStoppedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnUpdatedCallback;

                    void HandleTurnByTurnStarted();
                    void HandleTurnByTurnStopped();
                    void HandleTurnByTurnUpdated();

                };

            }
        }
    }
}
