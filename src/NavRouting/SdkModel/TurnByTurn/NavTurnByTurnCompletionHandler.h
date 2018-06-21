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
                class NavTurnByTurnCompletionHandler
                {
                public:

                    NavTurnByTurnCompletionHandler(INavTurnByTurnModel& turnByTurnModel,
                                                   INavRoutingModel& navRoutingModel,
                                                   Eegeo::Location::ILocationService& locationService,
                                                   float accuracyMultiplier,
                                                   float minDistanceToFinish);
                    ~NavTurnByTurnCompletionHandler();

                private:

                    INavTurnByTurnModel& m_turnByTurnModel;
                    INavRoutingModel& m_navRoutingModel;
                    Eegeo::Location::ILocationService& m_locationService;
                    float m_accuracyMultiplier;
                    float m_minDistanceToFinish;
                    int m_directionCount;
                    
                    Eegeo::Helpers::TCallback0<NavTurnByTurnCompletionHandler> m_turnByTurnStartedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnCompletionHandler> m_turnByTurnUpdatedCallback;

                    void HandleTurnByTurnStarted();
                    void HandleTurnByTurnUpdated();

                };
            }
        }
    }
}
