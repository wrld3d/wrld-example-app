// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuViewModel::MenuViewModel(bool isInitiallyOnScreen,
                                         Eegeo::Helpers::TIdentity identity,
                                         Reaction::View::IReactionControllerModel& reactionControllerModel)
            : m_identity(identity)
            , m_openViewModel(identity, reactionControllerModel)
            , m_screenViewModel(identity)
            , m_screenUpdatesSuspended(false)
            {
                m_onScreenState = m_screenViewModel.OnScreenState();
            }
            
            Eegeo::Helpers::TIdentity MenuViewModel::GetIdentity() const
            {
                return m_identity;
            }
            
            void MenuViewModel::AddToScreen()
            {
                m_screenViewModel.AddToScreen();
                m_onScreenState = 1.f;
            }
            
            void MenuViewModel::RemoveFromScreen()
            {
                if(!m_openViewModel.IsFullyClosed())
                {
                    m_openViewModel.Close();
                }
                
                m_screenViewModel.RemoveFromScreen();
                m_onScreenState = 0.f;
            }
            
            void MenuViewModel::SuspendScreenUpdates()
            {
                m_screenUpdatesSuspended = true;
            }
            
            void MenuViewModel::AllowScreenUpdates()
            {
                m_screenUpdatesSuspended = false;
                UpdateOnScreenState(m_onScreenState);
            }
            
            void MenuViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_onScreenState = onScreenState;
                
                if(!m_screenUpdatesSuspended)
                {
                    m_screenViewModel.UpdateOnScreenState(onScreenState);
                }
            }
            
            void MenuViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenViewModel.InsertOnScreenStateChangedCallback(callback);
            }
            
            void MenuViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenViewModel.RemoveOnScreenStateChangedCallback(callback);
            }
            
            bool MenuViewModel::IsFullyOffScreen() const
            {
                return m_screenViewModel.IsFullyOffScreen();
            }
            
            bool MenuViewModel::IsFullyOnScreen() const
            {
                return m_screenViewModel.IsFullyOnScreen();
            }
            
            float MenuViewModel::OnScreenState() const
            {
                return m_screenViewModel.OnScreenState();
            }
            
            bool MenuViewModel::IsAddedToScreen() const
            {
                return m_screenViewModel.IsAddedToScreen();
            }
            
            bool MenuViewModel::HasReactorControl() const
            {
                return m_openViewModel.HasReactorControl();
            }
            
            bool MenuViewModel::TryAcquireReactorControl()
            {
                return m_openViewModel.TryAcquireReactorControl();
            }
            
            void MenuViewModel::ReleaseReactorControl()
            {
                m_openViewModel.ReleaseReactorControl();
            }
            
            bool MenuViewModel::Open()
            {
                return m_openViewModel.Open();
            }
            
            bool MenuViewModel::Close()
            {
                return m_openViewModel.Close();
            }
            
            void MenuViewModel::UpdateOpenState(float openState)
            {
                m_openViewModel.UpdateOpenState(openState);
            }
            
            void MenuViewModel::InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>& callback)
            {
                m_openViewModel.InsertOpenStateChangedCallback(callback);
            }
            
            void MenuViewModel::RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>& callback)
            {
                m_openViewModel.RemoveOpenStateChangedCallback(callback);
            }
            
            bool MenuViewModel::IsFullyOpen() const
            {
                return m_openViewModel.IsFullyOpen();
            }
            
            bool MenuViewModel::IsFullyClosed() const
            {
                return m_openViewModel.IsFullyClosed();
            }
            
            float MenuViewModel::OpenState() const
            {
                return m_openViewModel.OpenState();
            }
            
            void MenuViewModel::AddSection(IMenuSectionViewModel& section)
            {
                m_sectionsViewModel.AddSection(section);
            }
            
            void MenuViewModel::RemoveSection(IMenuSectionViewModel& section)
            {
                m_sectionsViewModel.RemoveSection(section);
            }
            
            IMenuSectionViewModel& MenuViewModel::GetMenuSection(int index) const
            {
                return m_sectionsViewModel.GetMenuSection(index);
            }
        }
    }
}
