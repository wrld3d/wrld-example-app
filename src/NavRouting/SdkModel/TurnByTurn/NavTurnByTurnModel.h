
#pragma once

#include "INavTurnByTurnModel.h"
#include "LatLongAltitude.h"
#include "Location.h"
#include "NavRouting.h"
#include "ICallback.h"
#include "CallbackCollection.h"

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

                    float distanceToNextStepThreshold = 10.0f;
                    float updateRateSeconds = 1.0f;
                    float distanceForRecalculateRouteThreshold = 100.0f;
                };

                class NavTurnByTurnModel : public INavTurnByTurnModel {
                public:

                    bool TurnByTurnEnabled() const { return m_enabled; }

                    const Eegeo::Space::LatLong& GetClosestPointOnRoute() const { return m_closestPointOnRoute; }
                    double GetDistanceFromRoute() const { return m_distanceFromRoute; }
                    virtual double GetRemainingDuration() const { return m_remainingDuration; }
                    double GetRouteProgressParam() const { return m_paramAlongRoute; }
                    double GetRouteStepProgressParam() const { return m_paramAlongStep; }
                    int GetCurrentStepIndex() const { return m_currentStepIndex; }

                    NavTurnByTurnModel(const NavTurnByTurnConfig& config,
                                       INavRoutingModel& navRoutingModel,
                                       Eegeo::Location::ILocationService& locationService);
                    ~NavTurnByTurnModel();

                    void Start();
                    void Stop();

                    void Update(float dt);

                    void InsertStartedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveStartedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertStoppedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveStoppedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertUpdatedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveUpdatedCallback(Eegeo::Helpers::ICallback0& callback);


                    // Controller -
                    // Passes any messages needed for view (Remaining duration/distance, currentStep, etc)

                    // Work nicely with compass modes
                    // Advance current index correctly given thresholds

                    // Recalculate route detection

                    // Fraction/Expose stuff for route drawing to use.

                    // (Audio commands)

                private:

                    void UpdateTurnByTurn();

                    // NOTE: Check if this only returns the indoor position if you're IN the indoor map, in which case
                    // it's useless.
                    Eegeo::Location::ILocationService& m_locationService;
                    INavRoutingModel& m_navRoutingModel;
                    const NavTurnByTurnConfig m_config;

                    Eegeo::Helpers::CallbackCollection0 m_startedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_stoppedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_updateCallbacks;

                    Eegeo::Space::LatLong m_closestPointOnRoute;
                    double m_distanceFromRoute;
                    double m_remainingDuration;
                    double m_paramAlongRoute;
                    double m_paramAlongStep;
                    float m_updateTime;
                    int m_currentStepIndex;
                    bool m_enabled;

                };

            }

        }
    }

}