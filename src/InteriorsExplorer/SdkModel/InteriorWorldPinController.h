// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinController
            {
            public:
                
                InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                           Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                           InteriorsExplorerCameraController& cameraController);
                ~InteriorWorldPinController();
                
            private:
                
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                InteriorsExplorerCameraController& m_cameraController;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_interiorIdToWorldPinMap;
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerAddedCallback;
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerRemovedCallback;
                
                void HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
                void HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
            };
        }
    }
}