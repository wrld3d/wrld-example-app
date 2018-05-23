// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationViewModel.h"
#include "IAppModeModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationViewModel::MyPinCreationInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_screenControl(initiallyOnScreen, identity)
                , m_shouldOffsetViewButton(false)
                , m_canAddToScreen(true)
                , m_messageBus(messageBus)
                , m_appModeChangedCallback(this, &MyPinCreationInitiationViewModel::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }

            MyPinCreationInitiationViewModel::~MyPinCreationInitiationViewModel()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
            }

            ScreenControl::View::IScreenControlViewModel& MyPinCreationInitiationViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity MyPinCreationInitiationViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void MyPinCreationInitiationViewModel::AddToScreen()
            {
                if (m_canAddToScreen)
                {
                    m_screenControl.AddToScreen();
                }
            }

            void MyPinCreationInitiationViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void MyPinCreationInitiationViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void MyPinCreationInitiationViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void MyPinCreationInitiationViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool MyPinCreationInitiationViewModel::IsFullyOffScreen() const
            {
                return m_screenControl.IsFullyOffScreen();
            }

            bool MyPinCreationInitiationViewModel::IsFullyOnScreen() const
            {
                return m_screenControl.IsFullyOnScreen();
            }

            float MyPinCreationInitiationViewModel::OnScreenState() const
            {
                return m_screenControl.OnScreenState();
            }
            
            bool MyPinCreationInitiationViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }

            bool MyPinCreationInitiationViewModel::ShouldOffsetViewButton() const
            {
                return m_shouldOffsetViewButton;
            }

            void MyPinCreationInitiationViewModel::SetShouldOffsetViewButton(bool shouldOffset)
            {
                m_shouldOffsetViewButton = shouldOffset;
            }

            void MyPinCreationInitiationViewModel::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                m_canAddToScreen = (message.GetAppMode() != AppModes::SdkModel::AttractMode);
            }
        }
    }
}
