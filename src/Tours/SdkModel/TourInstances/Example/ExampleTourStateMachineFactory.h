// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "WorldPins.h"
#include <string>
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    class ExampleTourStateMachineFactory : private Eegeo::NonCopyable
                    {
                    public:
                        
                        ExampleTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                       bool interiorsEnabled,
                                                       InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                       Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus);
                        ~ExampleTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                        
                    private:
                        
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        
                        bool m_interiorsEnabled;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                    };
                }
            }
        }
    }
}