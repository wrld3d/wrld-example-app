// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationConfirmationViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationConfirmationViewModel::MyPinCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                                                                           bool initiallyOnScreen)
        : m_screenControl(initiallyOnScreen, identity)
        {
            
        }
        
        ScreenControlViewModel::IScreenControlViewModel& MyPinCreationConfirmationViewModel::GetScreenControlViewModel()
        {
            return m_screenControl;
        }
        
        Eegeo::Helpers::TIdentity MyPinCreationConfirmationViewModel::GetIdentity() const
        {
            return m_screenControl.GetIdentity();
        }
        
        void MyPinCreationConfirmationViewModel::AddToScreen()
        {
            m_screenControl.AddToScreen();
        }
        
        void MyPinCreationConfirmationViewModel::RemoveFromScreen()
        {
            m_screenControl.RemoveFromScreen();
        }
        
        void MyPinCreationConfirmationViewModel::UpdateOnScreenState(float onScreenState)
        {
            m_screenControl.UpdateOnScreenState(onScreenState);
        }
        
        void MyPinCreationConfirmationViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.InsertOnScreenStateChangedCallback(callback);
        }
        
        void MyPinCreationConfirmationViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.RemoveOnScreenStateChangedCallback(callback);
        }
        
        bool MyPinCreationConfirmationViewModel::IsFullyOffScreen() const
        {
            return m_screenControl.IsFullyOffScreen();
        }
        
        bool MyPinCreationConfirmationViewModel::IsFullyOnScreen() const
        {
            return m_screenControl.IsFullyOnScreen();
        }
        
        float MyPinCreationConfirmationViewModel::OnScreenState() const
        {
            return m_screenControl.OnScreenState();
        }
    }
}
