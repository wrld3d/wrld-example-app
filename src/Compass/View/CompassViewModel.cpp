// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewModel.h"
#include "IScreenControlView.h"

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

            ScreenControl::View::IMultiStateScreenControlViewModel& CompassViewModel::GetScreenControlViewModel()
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

            void CompassViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void CompassViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool CompassViewModel::IsOffScreen() const
            {
                return m_screenControl.IsOffScreen();
            }

            bool CompassViewModel::IsOnScreen() const
            {
                return m_screenControl.IsOnScreen();
            }

            ScreenControl::View::TScreenControlViewState CompassViewModel::GetState()
            {
                return m_screenControl.GetState();
            }

            void CompassViewModel::SetState(
                    ScreenControl::View::TScreenControlViewState screenControlViewState)
            {
                m_screenControl.SetState(screenControlViewState);
            }
        }
    }
}
