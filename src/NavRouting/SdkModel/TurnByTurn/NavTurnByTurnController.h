// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "Location.h"
#include "GpsMarker.h"

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
                                            Eegeo::Location::NavigationService& navigationService,
                                            GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel);
                    ~NavTurnByTurnController();

                    void Update(float dt);

                private:

                    INavTurnByTurnModel& m_turnByTurnModel;
                    INavRoutingModel& m_navRoutingModel;
                    Eegeo::Location::NavigationService& m_navigationService;
                    GpsMarker::SdkModel::GpsMarkerModel& m_gpsMarkerModel;

                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnStartedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnStoppedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnController> m_turnByTurnWillUpdateCallback;

                    void HandleTurnByTurnStarted();
                    void HandleTurnByTurnStopped();
                    void HandleTurnByTurnWillUpdate();

                };

            }
        }
    }
}
