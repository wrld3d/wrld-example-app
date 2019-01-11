// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavTurnByTurnModel.h"
#include "LatLongAltitude.h"
#include "Location.h"
#include "NavRouting.h"
#include "RouteData.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "InteriorsModelRepository.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                class NavTurnByTurnConfig {
                public:

                    float updateRateSeconds = 1.0f;
                    float distanceToPathRangeMeters = 10.0f;
                    float distanceToPathToTriggerReroute = 10.f;
                    float timeInSecondsToTriggerReroute = 10.0f;
                    float accuracyMultiplierToCompleteNavigation = 0.5f;
                    float minDistanceToCompleteNavigation = 5.0f;
                };

                class NavTurnByTurnModel : public INavTurnByTurnModel
                {
                public:

                    bool TurnByTurnEnabled() const { return m_enabled; }

                    const Eegeo::Space::LatLong& GetClosestPointOnRoute() const { return m_closestPointOnRoute; }
                    double GetDistanceFromRoute() const { return m_distanceFromRoute; }
                    virtual double GetRemainingDuration() const { return m_remainingDuration; }
                    double GetRouteProgressParam() const { return m_paramAlongRoute; }
                    double GetRouteStepProgressParam() const { return m_paramAlongStep; }
                    double GetDistanceToNextStep() const { return m_distanceToNextStep; }
                    int GetCurrentSectionIndex() const { return m_currentSectionIndex; }
                    int GetCurrentStepIndex() const { return m_currentStepIndex; }
                    int GetIndexOfPathSegmentStartVertex() const { return m_indexOfPathSegmentStartVertex; }

                    NavTurnByTurnModel(const NavTurnByTurnConfig& config,
                                       Eegeo::Location::ILocationService& locationService,
                                       Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository);
                    ~NavTurnByTurnModel();

                    void Start(const Eegeo::Routes::Webservice::RouteData& route);
                    void Stop();

                    void Update(float dt);

                    void InsertStartedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveStartedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertStoppedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveStoppedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertWillUpdateCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveWillUpdateCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertUpdatedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveUpdatedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& interiorLocationLostCallback);
                    void RemoveInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& interiorLocationLostCallback);

                private:

                    void UpdateTurnByTurn();
                    void DisableTurnByTurn();

                    bool IsTooFarFromPath(double distanceToRouteAtCurrentPoint);
                    bool HasLostLocationService();

                    const NavTurnByTurnConfig m_config;
                    Eegeo::Location::ILocationService& m_locationService;
                    Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                    Eegeo::Routes::Webservice::RouteData m_route;

                    Eegeo::Helpers::CallbackCollection0 m_startedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_stoppedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_willUpdateCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_updateCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_shouldRerouteCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_interiorLocationLostCallbacks;

                    Eegeo::Space::LatLong m_closestPointOnRoute;
                    double m_distanceFromRoute;
                    double m_remainingDuration;
                    double m_paramAlongRoute;
                    double m_paramAlongStep;
                    double m_distanceToNextStep;
                    float m_updateTime;
                    float m_secondsElapsedSinceOffRoute;
                    int m_currentSectionIndex;
                    int m_currentStepIndex;
                    int m_indexOfPathSegmentStartVertex;
                    bool m_enabled;
                    bool m_shouldDisable;

                };

            }

        }
    }

}