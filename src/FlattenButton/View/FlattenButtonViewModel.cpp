// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonViewModel::FlattenButtonViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
            {

            }

            ScreenControl::View::IScreenControlViewModel& FlattenButtonViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity FlattenButtonViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void FlattenButtonViewModel::AddToScreen()
            {
                m_screenControl.AddToScreen();
            }

            void FlattenButtonViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void FlattenButtonViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void FlattenButtonViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void FlattenButtonViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool FlattenButtonViewModel::IsFullyOffScreen() const
            {
                return m_screenControl.IsFullyOffScreen();
            }

            bool FlattenButtonViewModel::IsFullyOnScreen() const
            {
                return m_screenControl.IsFullyOnScreen();
            }

            float FlattenButtonViewModel::OnScreenState() const
            {
                return m_screenControl.OnScreenState();
            }
            
            bool FlattenButtonViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }
        }
    }
}
