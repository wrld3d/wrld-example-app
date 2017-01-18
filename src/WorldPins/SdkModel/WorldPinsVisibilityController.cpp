// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsVisibilityController.h"

#include <limits>

#include "InteriorsModel.h"
#include "IWorldPinsService.h"
#include "ScreenProperties.h"
#include "IWorldPinsRepository.h"
#include "WorldPinsVisibilityMessage.h"
#include "WorldPinVisibility.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsVisibilityController::WorldPinsVisibilityController(IWorldPinsRepository& worldPinsRepository,
                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                         const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                         const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                         ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            : m_worldPinsRepository(worldPinsRepository)
            , m_messageBus(messageBus)
            , m_visibilityMessageHandlerBinding(this, &WorldPinsVisibilityController::OnWorldPinsVisibilityMessage)
            , m_modality(0.f)
            , m_pinsVisible(false)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_sdkDomainEventBus(sdkDomainEventBus)
            , m_visibilityMask(WorldPins::SdkModel::WorldPinVisibility::All)
            , m_hideOutdoorPinsIndoors(true)
            {
                m_messageBus.SubscribeNative(m_visibilityMessageHandlerBinding);
                m_sdkDomainEventBus.Subscribe(m_visibilityMessageHandlerBinding);
            }
            
            WorldPinsVisibilityController::~WorldPinsVisibilityController()
            {
                m_messageBus.UnsubscribeNative(m_visibilityMessageHandlerBinding);
                m_sdkDomainEventBus.Unsubscribe(m_visibilityMessageHandlerBinding);
            }
            
            void WorldPinsVisibilityController::Update(float deltaSeconds)
            {
                for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                {
                    WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
                    UpdateWorldPin(worldPinItemModel, deltaSeconds);
                }
            }
            
            void WorldPinsVisibilityController::SetHideOutdoorPinsIndoors(bool hideOutdoorPinsIndoors)
            {
                m_hideOutdoorPinsIndoors = hideOutdoorPinsIndoors;
            }
            
            void WorldPinsVisibilityController::SetModality(float modality)
            {
                Eegeo_ASSERT(modality >= 0.f && modality <= 1.f, "Invalid modality value %f, valid range for modality is 0.0 to 1.0 inclusive.\n", modality);
                
                m_modality = modality;
            }
            
            int WorldPinsVisibilityController::GetVisibilityMask()
            {
                return m_visibilityMask;
            }
            
            void WorldPinsVisibilityController::SetVisibilityMask(int visibilityMask)
            {
                m_visibilityMask = visibilityMask;
            }
            
            bool WorldPinsVisibilityController::ShouldHidePin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel)
            {
                if(!m_pinsVisible)
                {
                    return true;
                }
                
                const bool showingInterior = m_interiorTransitionModel.InteriorIsVisible();
                const bool canShowInteriorPins = m_interiorInteractionModel.IsCollapsed();
                
                
                if((m_visibilityMask & worldPinItemModel.VisibilityMask()) == 0)
                {
                    return true;
                }
                
                if(m_modality > 0.0f)
                {
                    return true;
                }
                
                if(m_hideOutdoorPinsIndoors && showingInterior && !worldPinItemModel.IsInterior())
                {
                    return true;
                }
                
                if(!showingInterior && worldPinItemModel.IsInterior())
                {
                    return !worldPinItemModel.GetInteriorData().showInExterior;
                }
                
                // TODO: Remove when marker/label visibility for interiors handled by sdk.
                bool hidePinFromInteriorData =  false;
                if(showingInterior && worldPinItemModel.IsInterior())
                {
                    //hide if building and floor of pin not showing
                    const bool isSameBuilding = m_interiorInteractionModel.HasInteriorModel() ? (m_interiorInteractionModel.GetInteriorModel()->GetId() == worldPinItemModel.GetInteriorData().building) : false;
                    const bool isSameFloor = worldPinItemModel.GetInteriorData().floor == m_interiorInteractionModel.GetSelectedFloorIndex();
                    
                    hidePinFromInteriorData = !canShowInteriorPins || !isSameBuilding || !isSameFloor;
                }
                
                return hidePinFromInteriorData;
            }
            
            void WorldPinsVisibilityController::UpdateWorldPin(WorldPinItemModel& worldPinItemModel,
                                                          float deltaSeconds)
            {
                if(ShouldHidePin(worldPinItemModel))
                {
                    worldPinItemModel.Hide();
                }
                else
                {
                    worldPinItemModel.Show();
                }
                
                worldPinItemModel.Update(deltaSeconds);
            }
            
            void WorldPinsVisibilityController::Show()
            {
                m_pinsVisible = true;
            }
            
            void WorldPinsVisibilityController::Hide()
            {
                m_pinsVisible = false;
            }
            
            void WorldPinsVisibilityController::OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage &worldPinsVisibilityMessage)
            {
                if(worldPinsVisibilityMessage.ShouldSetVisible())
                {
                    Show();
                }
                else
                {
                    Hide();
                }
                
                m_visibilityMask = worldPinsVisibilityMessage.VisibilityMask();
            }
        }
    }
}
