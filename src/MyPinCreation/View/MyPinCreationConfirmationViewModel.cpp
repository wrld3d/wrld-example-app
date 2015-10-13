// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationViewModel::MyPinCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)

                : m_screenControl(initiallyOnScreen, identity)
                , m_openable(identity, reactionControllerModel)
            {

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

            void MyPinCreationConfirmationViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void MyPinCreationConfirmationViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void MyPinCreationConfirmationViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
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
            
            bool MyPinCreationConfirmationViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }

            bool MyPinCreationConfirmationViewModel::TryOpen()
            {
                return m_openable.TryAcquireReactorControl();
            }

            void MyPinCreationConfirmationViewModel::Close()
            {
                m_openable.ReleaseReactorControl();
            }
        }
    }
}
