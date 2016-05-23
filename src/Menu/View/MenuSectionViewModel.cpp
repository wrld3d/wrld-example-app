// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuSectionViewModel.h"
#include "IMenuModel.h"
#include "MenuJsonSerializer.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuSectionViewModel::MenuSectionViewModel(const std::string& name, const std::string& icon, IMenuModel& menuModel, bool isExpandable)
                : m_name(name)
                , m_icon(icon)
                , m_menuModel(menuModel)
                , m_isExpandable(isExpandable)
                , m_expanded(false)
            {
            }

            std::string MenuSectionViewModel::SerializeJson() const
            {
                return SerialiseMenuItemToJson(*this);
            }

            size_t MenuSectionViewModel::Size() const
            {
                if(m_isExpandable)
                {
                    if(!m_expanded)
                    {
                        return 1; // Header
                    }
                    else
                    {
                        return m_menuModel.GetItemCount() + 1; // Content + Header
                    }
                }
                else
                {
                    return m_menuModel.GetItemCount();
                }
            }

            size_t MenuSectionViewModel::GetTotalItemCount() const
            {
                return m_menuModel.GetItemCount();
            }

            MenuItemModel MenuSectionViewModel::GetItemAtIndex(int index) const
            {
                return m_menuModel.GetItemAtIndex(index);
            }

            void MenuSectionViewModel::Expand()
            {
                if(m_isExpandable && !m_expanded)
                {
                    m_expanded = true;
                    m_expandedChangedCallbacks.ExecuteCallbacks(*this, m_expanded);
                }
            }

            void MenuSectionViewModel::Contract()
            {
                if(m_isExpandable && m_expanded)
                {
                    m_expanded = false;
                    m_expandedChangedCallbacks.ExecuteCallbacks(*this, m_expanded);
                }
            }
            
            void MenuSectionViewModel::InsertExpandedChangedCallback(Eegeo::Helpers::ICallback2<IMenuSectionViewModel&, bool>& callback)
            {
                m_expandedChangedCallbacks.AddCallback(callback);
            }
            void MenuSectionViewModel::RemoveExpandedChangedCallback(Eegeo::Helpers::ICallback2<IMenuSectionViewModel&, bool>& callback)
            {
                m_expandedChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
