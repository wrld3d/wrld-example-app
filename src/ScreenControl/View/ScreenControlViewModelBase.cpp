// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            ScreenControlViewModelBase::ScreenControlViewModelBase(bool isInitiallyOnScreen)
                : m_addedToScreen(isInitiallyOnScreen)
            {

            }

            ScreenControlViewModelBase::~ScreenControlViewModelBase()
            {

            }

            void ScreenControlViewModelBase::AddToScreen()
            {
                m_addedToScreen = true;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
            }

            void ScreenControlViewModelBase::RemoveFromScreen()
            {
                m_addedToScreen = false;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
            }

            void ScreenControlViewModelBase::InsertOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_onScreenStateChangedCallbacks.AddCallback(callback);
            }

            void ScreenControlViewModelBase::RemoveOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_onScreenStateChangedCallbacks.RemoveCallback(callback);
            }

            bool ScreenControlViewModelBase::IsOffScreen() const
            {
                return !m_addedToScreen;
            }

            bool ScreenControlViewModelBase::IsOnScreen() const
            {
                return m_addedToScreen;
            }
        }
    }
}
