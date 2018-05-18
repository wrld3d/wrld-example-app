
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

                    float updateRateSeconds = 1.0f;
                    float distanceToPathRangeMeters = 10.0f;

                    // TODO: Recalculate route event config
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

                private:

                    void UpdateTurnByTurn();

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
                    double m_distanceToNextStep;
                    float m_updateTime;
                    int m_currentSectionIndex;
                    int m_currentStepIndex;
                    bool m_enabled;

                };

            }

        }
    }

}