// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            void SearchMenuView::CallVoidVoidMethod(const char* func)
            {
               
            }

            SearchMenuView::SearchMenuView(WindowsNativeState& nativeState,
                const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
            }

            void SearchMenuView::SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
            {
                
            }

            void SearchMenuView::RemoveSeachKeyboard()
            {
                CallVoidVoidMethod("removeSearchKeyboard");
            }

            void SearchMenuView::DisableEditText()
            {
                CallVoidVoidMethod("disableEditText");
            }

            void SearchMenuView::EnableEditText()
            {
                CallVoidVoidMethod("enableEditText");
            }

            void SearchMenuView::SetEditText(const std::string& searchText, bool isCategory)
            {
            }

            void SearchMenuView::SetSearchResultCount(int searchResultCount)
            {

            }

            void SearchMenuView::CollapseAll()
            {
                /*for (Menu::View::TSections::iterator it = MenuView::m_currentSections.begin(); it != m_currentSections.end(); ++it)
                {
                    (*it)->Contract();
                }

                UpdateMenuSectionViews(m_currentSections);*/
            }

            void SearchMenuView::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchPerformedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchPerformedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuView::SearchPerformed(const std::string& searchQuery)
            {
                m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
            }

            void SearchMenuView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuView::OnSearchCleared()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
            }

            void SearchMenuView::InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_searchItemSelectedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_searchItemSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuView::HandleSearchItemSelected(int index)
            {
               m_searchItemSelectedCallbacks.ExecuteCallbacks(index);
            }

            bool SearchMenuView::IsTableAnimating() const
            {
                return false;
            }

            void SearchMenuView::UpdateTableAnimation(float dt)
            {

            }

            void SearchMenuView::SetTableCanInteract(bool interact)
            {

            }
        }
    }
}