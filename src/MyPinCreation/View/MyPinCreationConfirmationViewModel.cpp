// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationViewModel::MyPinCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)

                : m_screenControl(initiallyOnScreen, identity)
                , m_openable(identity)
            {

            }

            void MyPinCreationConfirmationViewModel::Open()
            {
                if(TryOpen()){
                    m_openCallbacks.ExecuteCallbacks();
                }
            }

            void MyPinCreationConfirmationViewModel::InsertOpenCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_openCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationViewModel::RemoveOpenCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_openCallbacks.RemoveCallback(callback);
            }

            ScreenControl::View::IScreenControlViewModel& MyPinCreationConfirmationViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            OpenableControl::View::IOpenableControlViewModel& MyPinCreationConfirmationViewModel::GetOpenableControlViewModel()
            {
                return m_openable;
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

            void MyPinCreationConfirmationViewModel::InsertOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void MyPinCreationConfirmationViewModel::RemoveOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool MyPinCreationConfirmationViewModel::IsOffScreen() const
            {
                return m_screenControl.IsOffScreen();
            }

            bool MyPinCreationConfirmationViewModel::IsOnScreen() const
            {
                return m_screenControl.IsOnScreen();
            }

            bool MyPinCreationConfirmationViewModel::TryOpen()
            {
                return true;
            }

            void MyPinCreationConfirmationViewModel::Close()
            {

            }
        }
    }
}
