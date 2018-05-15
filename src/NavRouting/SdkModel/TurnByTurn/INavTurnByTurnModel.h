#pragma once

#include "Space.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                class INavTurnByTurnModel {
                public:

                    virtual ~INavTurnByTurnModel() {}

                    virtual bool TurnByTurnEnabled() const = 0;

                    virtual const Eegeo::Space::LatLong& GetClosestPointOnRoute() const  = 0;
                    virtual double GetDistanceFromRoute() const  = 0;
                    virtual double GetRemainingDuration() const = 0;
                    virtual double GetRouteProgressParam() const  = 0;
                    virtual double GetRouteStepProgressParam() const  = 0;
                    virtual int GetCurrentStepIndex() const = 0;

                    virtual void Start() = 0;
                    virtual void Stop() = 0;

                    virtual void Update(float dt) = 0;

                    virtual void InsertStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertStoppedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveStoppedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertUpdatedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveUpdatedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                };

            }

        }
    }

}