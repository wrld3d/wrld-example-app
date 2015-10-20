// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorWorldPinController.h"
#include "InteriorMarkerModelRepository.h"
#include "IWorldPinsService.h"
#include "InteriorMarkerModel.h"
#include "WorldPinInteriorData.h"
#include "WorldPinFocusData.h"
#include "InteriorId.h"
#include "InteriorWorldPinSelectionHandler.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorWorldPinController::InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                   Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                                   WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                   InteriorsExplorerCameraController& cameraController)
            : m_interiorController(interiorController)
            , m_markerRepository(markerRepository)
            , m_worldPinsService(worldPinsService)
            , m_cameraController(cameraController)
            , m_markerAddedCallback(this, &InteriorWorldPinController::HandleMarkerAdded)
            , m_markerRemovedCallback(this, &InteriorWorldPinController::HandleMarkerRemoved)
            {
                m_markerRepository.RegisterNotifyAddedCallback(m_markerAddedCallback);
                m_markerRepository.RegisterNotifyRemovedCallback(m_markerRemovedCallback);
            }
            
            InteriorWorldPinController::~InteriorWorldPinController()
            {
                m_markerRepository.UnregisterNotifyAddedCallback(m_markerAddedCallback);
                m_markerRepository.UnregisterNotifyRemovedCallback(m_markerRemovedCallback);
                
                for(std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator it = m_interiorIdToWorldPinMap.begin();
                    it != m_interiorIdToWorldPinMap.end();
                    ++it)
                {
                    WorldPins::SdkModel::WorldPinItemModel* pPinModel = it->second;
                    m_worldPinsService.RemovePin(pPinModel);
                }
                
                m_interiorIdToWorldPinMap.clear();
            }
            
            void InteriorWorldPinController::HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel)
            {
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) == m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController already has a pin with that Id");
                
                const float heightOffsetMetres = 0.0f;
                const bool isInterior = false;
                const int iconIndex = 11;
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData;
                
                // Don't have a human readable 'Name' for Interiors at this point. Can map IDS -> Names per app?
                ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("Interior", markerModel.GetInteriorId().Value());
                Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(markerModel.GetMarkerLatLongAltitude().GetLatitudeInDegrees(),
                                                                                    markerModel.GetMarkerLatLongAltitude().GetLongitudeInDegrees());
                
                InteriorWorldPinSelectionHandler* pSelectionHandler = Eegeo_NEW(InteriorWorldPinSelectionHandler)(markerModel.GetInteriorId(),
                                                                                                                  m_interiorController,
                                                                                                                  m_cameraController,
                                                                                                                  markerModel.GetMarkerLatLongAltitude().ToECEF()
                                                                                                                  );
                
                WorldPins::SdkModel::WorldPinItemModel* pItemModel = m_worldPinsService.AddPin(pSelectionHandler,
                                                                                               NULL,
                                                                                               worldPinFocusData,
                                                                                               isInterior,
                                                                                               worldPinInteriorData,
                                                                                               location,
                                                                                               iconIndex,
                                                                                               heightOffsetMetres,
                                                                                               WorldPins::SdkModel::WorldPinVisibility::World);
                m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()] = pItemModel;
            }
            
            void InteriorWorldPinController::HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel &markerModel)
            {
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) != m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController does not have a pin with that Id");
                
                WorldPins::SdkModel::WorldPinItemModel* pPinModel = m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()];
                m_worldPinsService.RemovePin(pPinModel);
                
                m_interiorIdToWorldPinMap.erase(markerModel.GetInteriorId().Value());
            }
        }
    }
}