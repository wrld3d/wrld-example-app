// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassController.h"
#include "VirtualKeyboardStateChangedMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            void CompassController::OnViewCycled()
            {
                m_messageBus.Publish(CompassViewCycledMessage());
            }

            void CompassController::OnCompassModeChangedMessage(const CompassModeChangedMessage& message)
            {
                m_view.SetRotationHighlight(m_isRotating || message.GetMode() == GpsMode::GpsCompassMode);
                switch (message.GetMode())
                {
                case  GpsMode::GpsDisabled:
                    m_view.ShowGpsDisabledView();
                    break;
                case GpsMode::GpsFollow:
                    m_view.ShowGpsFollowView();
                    break;
                case GpsMode::GpsCompassMode:
                    m_view.ShowGpsCompassModeView();
                    break;
                case GpsMode::GpsMode_Max:
                    Eegeo_ASSERT(false, "Invalid gps mode");
                    break;
                }
            }
            
            void CompassController::OnCompassModeUnauthorizedMessage(const CompassModeUnauthorizedMessage& message)
            {
                m_view.NotifyGpsUnauthorized();
            }

            void CompassController::OnCompassHeadingChangedMessage(const CompassHeadingUpdateMessage& message)
            {
                if (!m_viewModel.IsFullyOffScreen())
                {
                    m_view.SetHeadingRadians(message.GetHeadingRadians());
                }
            }

            void CompassController::OnScreenStateChangedCallback(ScreenControl::View::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void CompassController::OnMyPinCreationStateChangedMessage(const MyPinCreation::MyPinCreationStateChangedMessage& message)
            {
                switch (message.GetMyPinCreationStage())
                {
                    case MyPinCreation::Inactive:
                    {
                        if (m_appModeAllowsOpen)
                        {
                            m_viewModel.AddToScreen();
                        }
                    }break;
                    case MyPinCreation::Ring:
                    {
                        m_viewModel.RemoveFromScreen();
                    }break;
                    case MyPinCreation::Details:
                    {
                    }break;
                    default:
                    {
                        Eegeo_ASSERT(false, "Unknown MyPinCreationStage");
                    }
                }
            }
            
            void CompassController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AttractMode;
                
                if(m_appModeAllowsOpen)
                {
                    m_viewModel.AddToScreen();
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                }
            }

            void CompassController::OnVirtualKeyboardStateChangedMessage(const VirtualKeyboard::VirtualKeyboardStateChangedMessage& message)
            {
                if (m_appModeAllowsOpen)
                {
                    if (message.IsVirtualKeyboardVisible())
                    {
                        m_viewModel.RemoveFromScreen();
                    }
                    else
                    {
                        m_viewModel.AddToScreen();
                    }
                }
            }

            void CompassController::OnIsRotatingStateChangedMessage(const Compass::CompassIsRotatingStateChangedMessage& message)
            {
                m_isRotating = message.IsRotating();
                m_view.SetRotationHighlight(message.IsRotating());
            }

            CompassController::CompassController(  ICompassView& view,
                                                   ICompassViewModel& viewModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_appModeAllowsOpen(true)
                , m_viewStateCallback(this, &CompassController::OnScreenStateChangedCallback)
                , m_modeChangedHandler(this, &CompassController::OnCompassModeChangedMessage)
                , m_modeUnauthorizedHandler(this, &CompassController::OnCompassModeUnauthorizedMessage)
                , m_headingChangedHandler(this, &CompassController::OnCompassHeadingChangedMessage)
                , m_myPinCreationStateChangedMessageHandler(this, &CompassController::OnMyPinCreationStateChangedMessage)
                , m_viewCycledCallback(this, &CompassController::OnViewCycled)
                , m_appModeChangedHandler(this, &CompassController::OnAppModeChangedMessage)
                , m_virtualKeyboardStateChangedMessageHandler(this, &CompassController::OnVirtualKeyboardStateChangedMessage)
                , m_isRotatingStateChangedMessageHandler(this, &CompassController::OnIsRotatingStateChangedMessage)
                , m_isRotating(false)
            {
                m_messageBus.SubscribeUi(m_modeChangedHandler);
                m_messageBus.SubscribeUi(m_headingChangedHandler);
                m_messageBus.SubscribeUi(m_myPinCreationStateChangedMessageHandler);
                m_messageBus.SubscribeUi(m_modeUnauthorizedHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
                m_messageBus.SubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
                m_messageBus.SubscribeUi(m_isRotatingStateChangedMessageHandler);

                m_view.InsertCycledCallback(m_viewCycledCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);

                m_view.SetOnScreenStateToIntermediateValue(m_viewModel.OnScreenState());
            }

            CompassController::~CompassController()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveCycledCallback(m_viewCycledCallback);

                m_messageBus.UnsubscribeUi(m_isRotatingStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_messageBus.UnsubscribeUi(m_modeUnauthorizedHandler);
                m_messageBus.UnsubscribeUi(m_headingChangedHandler);
                m_messageBus.UnsubscribeUi(m_modeChangedHandler);
                m_messageBus.UnsubscribeUi(m_myPinCreationStateChangedMessageHandler);
            }
        }
    }
}
