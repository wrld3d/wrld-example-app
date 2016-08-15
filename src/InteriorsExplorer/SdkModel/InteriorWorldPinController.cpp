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
#include "MenuDragStateChangedMessage.h"
#include "SearchVendorNames.h"
#include "IInitialExperienceModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorWorldPinController::InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                                   WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                   Eegeo::Resources::Interiors::InteriorsCameraController& cameraController,
                                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                                   const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_markerRepository(markerRepository)
            , m_worldPinsService(worldPinsService)
            , m_cameraController(cameraController)
            , m_messageBus(messageBus)
            , m_markerAddedCallback(this, &InteriorWorldPinController::HandleMarkerAdded)
            , m_markerRemovedCallback(this, &InteriorWorldPinController::HandleMarkerRemoved)
            , m_menuDraggedCallback(this, &InteriorWorldPinController::HandleMenuDragged)
            , m_menuIsDragging(false)
            , m_initialExperienceModel(initialExperienceModel)
            {
                m_markerRepository.RegisterNotifyAddedCallback(m_markerAddedCallback);
                m_markerRepository.RegisterNotifyRemovedCallback(m_markerRemovedCallback);
                
                m_messageBus.SubscribeNative(m_menuDraggedCallback);
            }
            
            InteriorWorldPinController::~InteriorWorldPinController()
            {
                m_messageBus.UnsubscribeNative(m_menuDraggedCallback);
                
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
            
            const bool InteriorWorldPinController::PinInteractionAllowed(const std::string& interiorId) const
            {
                const bool cameraUnlocked = m_initialExperienceModel.LockedCameraStepsCompleted();
                return !m_menuIsDragging && cameraUnlocked &&
                    !m_interiorSelectionModel.IsInteriorSelected() &&
                    m_deferedRemovalMap.find(interiorId) == m_deferedRemovalMap.end();
            }
            
            void InteriorWorldPinController::Update(float dt)
            {
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator it;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator nextIt;
                for(it = m_deferedRemovalMap.begin(); it != m_deferedRemovalMap.end(); it = nextIt)
                {
                    nextIt = it;
                    ++nextIt;
                    m_worldPinsService.RemovePin(it->second);
                    m_interiorIdToWorldPinMap.erase(it->first);
                    m_deferedRemovalMap.erase(it);
                }
            }
            
            void InteriorWorldPinController::HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel)
            {
                if(m_deferedRemovalMap.erase(markerModel.GetInteriorId().Value()) != 0)
                {
                    return;
                }
                
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) == m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController already has a pin with that Id");
                
                const float heightOffsetMetres = 0.0f;
                const bool isInterior = false;
                const std::string indoorMapEntryIconKey = "indoor_map";
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData;
                
                ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(markerModel.GetInteriorName(),
                                                                                     markerModel.GetInteriorOwner(),
                                                                                     Search::InteriorVendorName);
                
                Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(markerModel.GetMarkerLatLongAltitude().GetLatitudeInDegrees(),
                                                                                    markerModel.GetMarkerLatLongAltitude().GetLongitudeInDegrees());
                
                InteriorWorldPinSelectionHandler* pSelectionHandler = Eegeo_NEW(InteriorWorldPinSelectionHandler)(markerModel.GetInteriorId(),
                                                                                                                  m_interiorSelectionModel,
                                                                                                                  m_cameraController,
                                                                                                                  markerModel.GetMarkerLatLongAltitude().ToECEF(),
                                                                                                                  *this);
                
                WorldPins::SdkModel::WorldPinItemModel* pItemModel = m_worldPinsService.AddPin(pSelectionHandler,
                                                                                               NULL,
                                                                                               worldPinFocusData,
                                                                                               isInterior,
                                                                                               worldPinInteriorData,
                                                                                               location,
                                                                                               indoorMapEntryIconKey,
                                                                                               heightOffsetMetres,
                                                                                               WorldPins::SdkModel::WorldPinVisibility::World);
                m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()] = pItemModel;
            }
            
            void InteriorWorldPinController::HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel &markerModel)
            {
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) != m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController does not have a pin with that Id");
                
                WorldPins::SdkModel::WorldPinItemModel* pPinModel = m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()];
                
                m_deferedRemovalMap[markerModel.GetInteriorId().Value()] = pPinModel;
            }
            
            void InteriorWorldPinController::HandleMenuDragged(const Menu::MenuDragStateChangedMessage &message)
            {
                m_menuIsDragging = message.IsDragging();
            }
        }
    }
}