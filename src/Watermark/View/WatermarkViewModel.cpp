// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkViewModel::WatermarkViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
            {

            }

            ScreenControl::View::IScreenControlViewModel& WatermarkViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity WatermarkViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void WatermarkViewModel::AddToScreen()
            {
                m_screenControl.AddToScreen();
            }

            void WatermarkViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void WatermarkViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void WatermarkViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool WatermarkViewModel::IsOffScreen() const
            {
                return m_screenControl.IsOffScreen();
            }

            bool WatermarkViewModel::IsOnScreen() const
            {
                return m_screenControl.IsOnScreen();
            }
        }
    }
}
