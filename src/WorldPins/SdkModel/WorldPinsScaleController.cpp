// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsScaleController.h"

#include <limits>

#include "InteriorsModel.h"
#include "IWorldPinsService.h"
#include "ScreenProperties.h"
#include "RenderCamera.h"
#include "IWorldPinsRepository.h"
#include "WorldPinsVisibilityMessage.h"
#include "InteriorController.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsScaleController::WorldPinsScaleController(IWorldPinsRepository& worldPinsRepository,
                                                               IWorldPinsService& worldPinsService,
                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                               Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                               ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
                : m_worldPinsRepository(worldPinsRepository)
                , m_worldPinsService(worldPinsService)
                , m_messageBus(messageBus)
                , m_visibilityMessageHandlerBinding(this, &WorldPinsScaleController::OnWorldPinsVisibilityMessage)
                , m_modality(0.f)
                , m_visibilityScale(0.f)
                , m_targetVisibilityScale(1.f)
                , m_visibilityAnimationDuration(0.2f)
                , m_interiorController(interiorController)
                , m_sdkDomainEventBus(sdkDomainEventBus)
                , m_visibilityMask(WorldPins::SdkModel::WorldPinVisibility::All)
            {
                m_messageBus.SubscribeNative(m_visibilityMessageHandlerBinding);
                m_sdkDomainEventBus.Subscribe(m_visibilityMessageHandlerBinding);
            }

            WorldPinsScaleController::~WorldPinsScaleController()
            {
                m_messageBus.UnsubscribeNative(m_visibilityMessageHandlerBinding);
                m_sdkDomainEventBus.Unsubscribe(m_visibilityMessageHandlerBinding);
            }

            void WorldPinsScaleController::Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera)
            {
                if(m_visibilityScale < m_targetVisibilityScale)
                {
                    m_visibilityScale = Eegeo::Min(m_visibilityScale + deltaSeconds/m_visibilityAnimationDuration, m_targetVisibilityScale);
                }
                else if(m_visibilityScale > m_targetVisibilityScale)
                {
                    m_visibilityScale = Eegeo::Max(m_visibilityScale - deltaSeconds/m_visibilityAnimationDuration, m_targetVisibilityScale);
                }

                for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                {
                    WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
                    UpdateWorldPin(worldPinItemModel, deltaSeconds, renderCamera);
                    const float globalScale = 1.f - m_modality;
                    float scale = globalScale  * worldPinItemModel.TransitionStateValue() * m_visibilityScale;
                    m_worldPinsService.UpdatePinScale(worldPinItemModel, scale);
                }
            }

            void WorldPinsScaleController::SetModality(float modality)
            {
                Eegeo_ASSERT(modality >= 0.f && modality <= 1.f, "Invalid modality value %f, valid range for modality is 0.0 to 1.0 inclusive.\n", modality);

                m_modality = modality;
            }
            
            bool WorldPinsScaleController::ShouldHidePin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                                         const Eegeo::Camera::RenderCamera& renderCamera)
            {
                const bool showingInterior = m_interiorController.InteriorIsVisible();
                
                if((m_visibilityMask & worldPinItemModel.VisibilityMask()) == 0)
                {
                    return true;
                }
                
                if(showingInterior && !worldPinItemModel.IsInterior())
                {
                    return true;
                }
                
                if(!showingInterior && worldPinItemModel.IsInterior())
                {
                    return !worldPinItemModel.GetInteriorData().showInExterior;
                }
                
                bool hidePinFromInteriorData =  false;
                if(showingInterior && worldPinItemModel.IsInterior())
                {
                    //hide if building and floor of pin not showing
                    const Eegeo::Resources::Interiors::InteriorsModel* pInteriorModel = NULL;

                    hidePinFromInteriorData = !(worldPinItemModel.GetInteriorData().floor == m_interiorController.GetCurrentFloorIndex() &&
                             m_interiorController.TryGetCurrentModel(pInteriorModel) &&
                             worldPinItemModel.GetInteriorData().building == pInteriorModel->GetId());
                }
                
                // hide when close to edge of screen
                Eegeo::v2 screenLocation;
                GetScreenLocation(worldPinItemModel, screenLocation, renderCamera);
                
                const float ratioX = screenLocation.GetX() / renderCamera.GetViewportWidth();
                const float ratioY = screenLocation.GetY() / renderCamera.GetViewportHeight();
                const bool hidePinFromScreenPosition = (ratioX < 0.1f) || (ratioX > 0.9f) || (ratioY < 0.15f) || (ratioY > 0.9f);
                
                return hidePinFromScreenPosition || hidePinFromInteriorData;
            }

            void WorldPinsScaleController::UpdateWorldPin(WorldPinItemModel& worldPinItemModel,
                    float deltaSeconds,
                    const Eegeo::Camera::RenderCamera& renderCamera)
            {
                if(ShouldHidePin(worldPinItemModel, renderCamera))
                {
                    worldPinItemModel.Hide();
                }
                else
                {
                    worldPinItemModel.Show();
                }

                worldPinItemModel.Update(deltaSeconds);
            }

            void WorldPinsScaleController::GetScreenLocation(const WorldPinItemModel& worldPinItemModel,
                    Eegeo::v2& screenLocation,
                    const Eegeo::Camera::RenderCamera& renderCamera) const
            {
                Eegeo::dv3 ecefLocation;
                m_worldPinsService.GetPinEcefAndScreenLocations(worldPinItemModel, ecefLocation, screenLocation);
                Eegeo::v3 cameraLocal = (ecefLocation - renderCamera.GetEcefLocation()).ToSingle();
                Eegeo::v3 screenPos;
                renderCamera.Project(cameraLocal, screenPos);
                screenLocation.Set(screenPos.GetX(), screenPos.GetY());
            }

            void WorldPinsScaleController::Show()
            {
                m_targetVisibilityScale = 1.0f;
            }

            void WorldPinsScaleController::Hide()
            {
                m_targetVisibilityScale = 0.0f;
            }

            void WorldPinsScaleController::OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage &worldPinsVisibilityMessage)
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
