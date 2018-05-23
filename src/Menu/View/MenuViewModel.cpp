// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuViewModel::MenuViewModel(bool isInitiallyOnScreen,
                                         Eegeo::Helpers::TIdentity identity)
            : m_identity(identity)
            , m_openViewModel(identity)
            , m_screenViewModel(identity)
            {
            }

            Eegeo::Helpers::TIdentity MenuViewModel::GetIdentity() const
            {
                return m_identity;
            }
            
            void MenuViewModel::AddToScreen()
            {
                m_screenViewModel.AddToScreen();
            }
            
            void MenuViewModel::RemoveFromScreen()
            {
                if(!m_openViewModel.IsClosed())
                {
                    m_openViewModel.Close();
                }
                
                m_screenViewModel.RemoveFromScreen();
            }
            
            void MenuViewModel::InsertOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_screenViewModel.InsertOnScreenStateChangedCallback(callback);
            }
            
            void MenuViewModel::RemoveOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_screenViewModel.RemoveOnScreenStateChangedCallback(callback);
            }
            
            bool MenuViewModel::IsOffScreen() const
            {
                return m_screenViewModel.IsOffScreen();
            }
            
            bool MenuViewModel::IsOnScreen() const
            {
                return m_screenViewModel.IsOnScreen();
            }

            void MenuViewModel::Open()
            {
                m_openViewModel.Open();
            }
            
            void MenuViewModel::Close()
            {
                m_openViewModel.Close();
            }
            
            void MenuViewModel::InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback1<OpenableControl::View::IOpenableControlViewModel&>& callback)
            {
                m_openViewModel.InsertOpenStateChangedCallback(callback);
            }
            
            void MenuViewModel::RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback1<OpenableControl::View::IOpenableControlViewModel&>& callback)
            {
                m_openViewModel.RemoveOpenStateChangedCallback(callback);
            }
            
            bool MenuViewModel::IsOpen() const
            {
                return m_openViewModel.IsOpen();
            }
            
            bool MenuViewModel::IsClosed() const
            {
                return m_openViewModel.IsClosed();
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
