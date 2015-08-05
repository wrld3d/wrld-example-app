// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorPinsVisibilityMessage.h"
#include "MapMode.h"
#include "InteriorId.h"
#include "Metrics.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModel : private Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorsController& controller,
                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       MapMode::SdkModel::IMapModeModel& mapModeModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       Metrics::IMetricsService& metricsService);
                ~InteriorsExplorerModel();
                
                void SelectFloor(int floor);

            private:
                
                void OnControllerStateChanged();
                void OnExit(const InteriorsExplorerExitMessage& message);
                void OnSelectFloor(const InteriorsExplorerSelectFloorMessage& message);
                void OnChangePinVisibility(const InteriorPinsVisibilityMessage& message);

                Eegeo::Resources::Interiors::InteriorsController& m_controller;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                MapMode::SdkModel::IMapModeModel& m_mapModeModel;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerStateChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerExitMessage&> m_exitCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorPinsVisibilityMessage&> m_changePinVisibilityCallback;

                void OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedCallback;

                bool m_previouslyInMapMode;

            };
        }
    }
}