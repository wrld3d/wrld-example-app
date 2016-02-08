// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "ICallback.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorId.h"
#include "Metrics.h"
#include "AppModes.h"
#include "InteriorsExplorer.h"
#include "VisualMap.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModel : private Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorController& controller,
                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       VisualMap::SdkModel::IVisualMapService& visualMapService,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                       Metrics::IMetricsService& metricsService);
                ~InteriorsExplorerModel();
                
                void SelectFloor(int floor);
                
                void ShowInteriorExplorer();
                void ShowInteriorExplorer(bool fromWithinAnotherInterior);
                void HideInteriorExplorer();
                void Exit();
                
                void ChangeToInteriorMapState();
                void ResumePreviousMapState();
                
                void InsertInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                
                void OnControllerStateChanged();
                void OnControllerVisibilityChanged();
                void OnControllerFloorChanged();
                
                void OnExit(const InteriorsExplorerExitMessage& message);
                void OnSelectFloor(const InteriorsExplorerSelectFloorMessage& message);
                
                void PublishInteriorExplorerStateChange();

                Eegeo::Resources::Interiors::InteriorController& m_controller;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                VisualMap::SdkModel::IVisualMapService& m_visualMapService;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerStateChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerVisibilityChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerFloorChangedCallback;
                
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerExitMessage&> m_exitCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;
                
                bool m_interiorExplorerEnabled;
                Eegeo::Helpers::CallbackCollection0 m_interiorExplorerExitedCallbacks;
            };
        }
    }
}