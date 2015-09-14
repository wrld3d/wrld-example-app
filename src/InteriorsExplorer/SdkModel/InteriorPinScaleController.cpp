// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinScaleController.h"
#include "InteriorsPinsController.h"
#include "IAppModeModel.h"
#include "MyPinCreationStage.h"

namespace ExampleApp
{

    
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorPinScaleController::InteriorPinScaleController(Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                                   AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_interiorsPinsController(interiorsPinsController)
            , m_appModeModel(appModeModel)
            , m_messageBus(messageBus)
            , m_modalMenuState(Closed)
            , m_myPinCreateOpen(false)
            , m_modalityChangedCallback(this, &InteriorPinScaleController::OnModalityChangedMessage)
            , m_myPinCreationStateChangedCallback(this, &InteriorPinScaleController::OnMyPinCreationStateChanged)
            , m_appModeChangedCallback(this, &InteriorPinScaleController::OnAppModeChanged)
            {
                m_messageBus.SubscribeNative(m_modalityChangedCallback);
                m_messageBus.SubscribeUi(m_myPinCreationStateChangedCallback);
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            }
            
            InteriorPinScaleController::~InteriorPinScaleController()
            {
                m_messageBus.UnsubscribeNative(m_modalityChangedCallback);
                m_messageBus.SubscribeUi(m_myPinCreationStateChangedCallback);
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }
  
            void InteriorPinScaleController::OnModalityChangedMessage(const Modality::ModalityChangedMessage& message)
            {
                const float modalityParam = message.Modality();
                
                if (modalityParam == 0.f)
                {
                    m_modalMenuState = Closed;
                }
                else if (modalityParam == 1.f)
                {
                    m_modalMenuState = Open;
                }
                else
                {
                    m_modalMenuState = (m_modalMenuState == Closed || m_modalMenuState == Opening) ? Opening : Closing;
                }
                
                UpdateInteriorPinsHiddenState();
            }
            
            void InteriorPinScaleController::OnMyPinCreationStateChanged(const MyPinCreation::MyPinCreationStateChangedMessage& message)
            {
                const MyPinCreation::MyPinCreationStage& myPinCreationStage = message.GetMyPinCreationStage();
                m_myPinCreateOpen = myPinCreationStage != MyPinCreation::Inactive;
                UpdateInteriorPinsHiddenState();
            }
            
            void InteriorPinScaleController::OnAppModeChanged()
            {
                UpdateInteriorPinsHiddenState();
            }
            
            bool InteriorPinScaleController::ShouldHidePins() const
            {
                bool hidePins = (m_modalMenuState == Open) ||
                                (m_modalMenuState == Opening) ||
                                m_myPinCreateOpen ||
                                (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode);
                return hidePins;
            }
            
            void InteriorPinScaleController::UpdateInteriorPinsHiddenState()
            {
                const bool hidePins = ShouldHidePins();
            
                m_interiorsPinsController.SetForcedHidden(hidePins);
            }
            

        }
    }
}