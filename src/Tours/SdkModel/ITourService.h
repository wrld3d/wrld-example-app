// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class ITourService
            {
            public:
                virtual ~ITourService() { }
                
                virtual bool IsTourActive() const = 0;
                
                virtual void AddTour(const TourModel& tourModel, States::ITourStateMachine& tourStateMachine) = 0;
                
                virtual void RemoveTour(const TourModel& tourModel) = 0;
                
                virtual void StartCurrentActiveTour(const TourModel& tourModel, const int atCard) = 0;
                
                virtual void EnqueueNextTour(const TourModel& tourModel) = 0;
                
                virtual void EndCurrentActiveTour() = 0;
                
                virtual void SetActiveTourState(int activeStateIndex) = 0;
                
                virtual void UpdateCurrentTour(float dt) = 0;
                
                virtual void RegisterTourStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void UnregisterTourStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RegisterTourEndedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void UnregisterTourEndedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
