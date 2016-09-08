// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuInitiationViewModel.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            DirectionsMenuInitiationViewModel::DirectionsMenuInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
                , m_shouldOffsetViewButton(false)
            {

            }

            ScreenControl::View::IScreenControlViewModel& DirectionsMenuInitiationViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity DirectionsMenuInitiationViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void DirectionsMenuInitiationViewModel::AddToScreen()
            {
                m_screenControl.AddToScreen();
            }

            void DirectionsMenuInitiationViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void DirectionsMenuInitiationViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void DirectionsMenuInitiationViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void DirectionsMenuInitiationViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool DirectionsMenuInitiationViewModel::IsFullyOffScreen() const
            {
                return m_screenControl.IsFullyOffScreen();
            }

            bool DirectionsMenuInitiationViewModel::IsFullyOnScreen() const
            {
                return m_screenControl.IsFullyOnScreen();
            }

            float DirectionsMenuInitiationViewModel::OnScreenState() const
            {
                return m_screenControl.OnScreenState();
            }
            
            bool DirectionsMenuInitiationViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }

            bool DirectionsMenuInitiationViewModel::ShouldOffsetViewButton() const
            {
                return m_shouldOffsetViewButton;
            }

            void DirectionsMenuInitiationViewModel::SetShouldOffsetViewButton(bool shouldOffset)
            {
                m_shouldOffsetViewButton = shouldOffset;
            }
        }
    }
}
