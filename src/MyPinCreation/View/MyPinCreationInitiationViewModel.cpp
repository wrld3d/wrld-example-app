// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationViewModel::MyPinCreationInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
                , m_shouldOffsetViewButton(false)
            {

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
                m_screenControl.AddToScreen();
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
        }
    }
}
