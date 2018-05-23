// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            ScreenControlViewModelBase::ScreenControlViewModelBase(bool isInitiallyOnScreen)
                : m_onScreenState(1.f)
                , m_addedToScreen(isInitiallyOnScreen)
            {

            }

            ScreenControlViewModelBase::~ScreenControlViewModelBase()
            {

            }

            void ScreenControlViewModelBase::AddToScreen()
            {
                m_addedToScreen = true;
                float onScreenState = OnScreenState();
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, onScreenState);
            }

            void ScreenControlViewModelBase::RemoveFromScreen()
            {
                m_addedToScreen = false;
                float onScreenState = OnScreenState();
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, onScreenState);
            }

            void ScreenControlViewModelBase::UpdateOnScreenState(float onScreenState)
            {
                Eegeo_ASSERT(onScreenState >= 0.f && onScreenState <= 1.f, "Invalid value %f for screen state, valid range for UI on-screen-state is 0.0 to 1.0 inclusive.\n", onScreenState);
                m_onScreenState = onScreenState;
                if(m_addedToScreen)
                {
                    m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, m_onScreenState);
                }
            }

            void ScreenControlViewModelBase::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback)
            {
                m_onScreenStateChangedCallbacks.AddCallback(callback);
            }

            void ScreenControlViewModelBase::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback)
            {
                m_onScreenStateChangedCallbacks.RemoveCallback(callback);
            }

            bool ScreenControlViewModelBase::IsFullyOffScreen() const
            {
                return OnScreenState() == 0.f;
            }

            bool ScreenControlViewModelBase::IsFullyOnScreen() const
            {
                return OnScreenState() == 1.f;
            }

            float ScreenControlViewModelBase::OnScreenState() const
            {
                return m_addedToScreen ? m_onScreenState : 0.0f;
            }
            
            bool ScreenControlViewModelBase::IsAddedToScreen() const
            {
                return m_addedToScreen;
            }
        }
    }
}
