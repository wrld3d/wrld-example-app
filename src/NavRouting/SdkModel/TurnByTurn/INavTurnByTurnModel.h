// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Space.h"
#include "ICallback.h"
#include "Routes.h"

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
                    virtual double GetDistanceToNextStep() const = 0;
                    virtual double GetRouteProgressParam() const  = 0;
                    virtual double GetRouteStepProgressParam() const  = 0;
                    virtual int GetCurrentSectionIndex() const = 0;
                    virtual int GetCurrentStepIndex() const = 0;
                    virtual int GetIndexOfPathSegmentStartVertex() const = 0;

                    virtual void Start(const Eegeo::Routes::Webservice::RouteData& route) = 0;
                    virtual void Stop() = 0;

                    virtual void Update(float dt) = 0;

                    virtual void InsertStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertStoppedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveStoppedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertWillUpdateCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveWillUpdateCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertUpdatedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveUpdatedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& interiorLocationLostCallback) = 0;
                    virtual void RemoveInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& interiorLocationLostCallback) = 0;
                };

            }

        }
    }

}