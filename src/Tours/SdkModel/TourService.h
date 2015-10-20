// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "Types.h"
#include "Tours.h"
#include "ITourService.h"
#include "TourModel.h"
#include "BidirectionalBus.h"
#include <stack>
#include "SdkModelDomainEventBus.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            struct SuspendedTour
            {
            public:
                
                SuspendedTour(TourModel& tour, int card)
                {
                    this->card = card;
                    this->tour = tour;
                }
                
                SuspendedTour()
                {
                    card = -1;
                    tour = TourModel::Empty();
                }
                
                int card;
                TourModel tour;
            };
            
            class TourService : public ITourService, private Eegeo::NonCopyable
            {
                ITourRepository& m_repository;
                Camera::IToursCameraTransitionController& m_cameraTransitionController;
                std::map<std::string, States::ITourStateMachine*> m_pTourToStateMachineMapping;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                
                TourModel m_activeTourModel;
                TourModel m_nextTourModel;
                bool m_hasActiveTour;
                bool m_suspendCurrentTour;
                int m_activeTourState;
                States::ITourStateMachine* m_pActiveTourStateMachine;
                
                std::stack<SuspendedTour> m_previousActiveToursStack;
                
                Eegeo::Helpers::CallbackCollection0 m_tourStartedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_tourEndedCallbacks;
                
            public:
                TourService(ITourRepository& repository,
                            Camera::IToursCameraTransitionController& cameraTransitionController,
                            ExampleAppMessaging::TMessageBus& messageBus,
                            ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                
                ~TourService();
                
                bool IsTourActive() const;
                
                // TourService::AddTour takes ownership of tourStateMachine and assumes it is dynamically allocated by Eegeo_NEW
                void AddTour(const TourModel& tourModel, States::ITourStateMachine& tourStateMachine);
                
                void RemoveTour(const TourModel& tourModel);
                
                void StartCurrentActiveTour(const TourModel& tourModel, const int atCard);
                
                void EnqueueNextTour(const TourModel& tourModel);
                
                void EndCurrentActiveTour();
                
                void SetActiveTourState(int activeStateIndex);
                
                void UpdateCurrentTour(float dt);
                
                void RegisterTourStartedCallback(Eegeo::Helpers::ICallback0& callback);
                void UnregisterTourStartedCallback(Eegeo::Helpers::ICallback0& callback);
                void RegisterTourEndedCallback(Eegeo::Helpers::ICallback0& callback);
                void UnregisterTourEndedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
