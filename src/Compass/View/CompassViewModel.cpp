// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewModel::CompassViewModel(Eegeo::Helpers::TIdentity identity,
                                               bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
            {

            }

            ScreenControl::View::IScreenControlViewModel& CompassViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity CompassViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void CompassViewModel::AddToScreen()
            {
                m_screenControl.AddToScreen();
            }

            void CompassViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void CompassViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void CompassViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void CompassViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool CompassViewModel::IsFullyOffScreen() const
            {
                return m_screenControl.IsFullyOffScreen();
            }

            bool CompassViewModel::IsFullyOnScreen() const
            {
                return m_screenControl.IsFullyOnScreen();
            }

            float CompassViewModel::OnScreenState() const
            {
                return m_screenControl.OnScreenState();
            }
            
            bool CompassViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }
        }
    }
}
