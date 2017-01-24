// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorWorldPinController.h"
#include "InteriorSelectionModel.h"
#include "MenuDragStateChangedMessage.h"
#include "IInitialExperienceModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorWorldPinController::InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                                   const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_messageBus(messageBus)
            , m_menuDraggedCallback(this, &InteriorWorldPinController::HandleMenuDragged)
            , m_menuIsDragging(false)
            , m_initialExperienceModel(initialExperienceModel)
            {
                m_messageBus.SubscribeNative(m_menuDraggedCallback);
            }
            
            InteriorWorldPinController::~InteriorWorldPinController()
            {
                m_messageBus.UnsubscribeNative(m_menuDraggedCallback);
            }
            
            const bool InteriorWorldPinController::PinInteractionAllowed(const std::string& interiorId) const
            {
                const bool cameraUnlocked = m_initialExperienceModel.LockedCameraStepsCompleted();
                return !m_menuIsDragging && cameraUnlocked &&
                    !m_interiorSelectionModel.IsInteriorSelected();
            }
            
            void InteriorWorldPinController::HandleMenuDragged(const Menu::MenuDragStateChangedMessage &message)
            {
                m_menuIsDragging = message.IsDragging();
            }
        }
    }
}