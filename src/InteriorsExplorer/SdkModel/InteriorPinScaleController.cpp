// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinScaleController.h"
#include "InteriorsPinsController.h"
#include "IAppModeModel.h"

namespace ExampleApp
{

    
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorPinScaleController::InteriorPinScaleController(Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                                   IAppModeModel& appModeModel,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_interiorsPinsController(interiorsPinsController)
            , m_appModeModel(appModeModel)
            , m_messageBus(messageBus)
            , m_modalMenuOpen(false)
            , m_modalityChangedCallback(this, &InteriorPinScaleController::OnModalityChangedMessage)
            , m_appModeChangedCallback(this, &InteriorPinScaleController::OnAppModeChanged)
            {
                m_messageBus.SubscribeNative(m_modalityChangedCallback);
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            }
            
            InteriorPinScaleController::~InteriorPinScaleController()
            {
                m_messageBus.UnsubscribeNative(m_modalityChangedCallback);
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }
  
            void InteriorPinScaleController::OnModalityChangedMessage(const Modality::ModalityChangedMessage& message)
            {
                m_modalMenuOpen = message.Modality() > 0.f;
                UpdateInteriorPinsHiddenState();
            }
            
            void InteriorPinScaleController::OnAppModeChanged()
            {
                UpdateInteriorPinsHiddenState();
            }
            
            
            void InteriorPinScaleController::UpdateInteriorPinsHiddenState()
            {
                bool hidePins = m_modalMenuOpen || (m_appModeModel.GetAppMode() == InteriorMode);
            
                m_interiorsPinsController.SetForcedHidden(hidePins);
            }
            

        }
    }
}