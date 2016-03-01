// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuView::SearchMenuView(WindowsNativeState& nativeState,
                const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
                , m_currentSections(0)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.SearchMenuView");

                mSetSearchSection.SetupMethod(m_uiViewClass, m_uiView, "SetSearchSection");
                mDisableEditText.SetupMethod(m_uiViewClass, m_uiView, "DisableEditText");
                mEnableEditText.SetupMethod(m_uiViewClass, m_uiView, "EnableEditText");
                mSetEditText.SetupMethod(m_uiViewClass, m_uiView, "SetEditText");
                mSetSearchResultCount.SetupMethod(m_uiViewClass, m_uiView, "SetSearchResultCount");
            }

            void SearchMenuView::SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
            {
                int resultCount = static_cast<int>(searchSection.Size());

                if (resultCount <= 0)
                {
                    return;
                }

                array<System::String^>^ searchResultArray = gcnew array<System::String^>(resultCount);

                for (int i = 0; i < resultCount; ++i)
                {
                    System::String^ str = ConvertUTF8ToManagedString(searchSection.GetItemAtIndex(i).SerializeJson());
                    searchResultArray[i] = str;
                }

                mSetSearchSection(System::String::Empty, searchResultArray);
            }

            void SearchMenuView::RemoveSeachKeyboard()
            {
                
            }

            void SearchMenuView::DisableEditText()
            {
                mDisableEditText();
            }

            void SearchMenuView::EnableEditText()
            {
                mEnableEditText();
            }

            void SearchMenuView::SetEditText(const std::string& searchText, bool isCategory)
            {
                mSetEditText(gcnew System::String(searchText.c_str()), isCategory);
            }

            void SearchMenuView::SetSearchResultCount(int searchResultCount)
            {
                mSetSearchResultCount(searchResultCount);
            }

            void SearchMenuView::CollapseAll()
            {
                for (Menu::View::TSections::iterator it = m_currentSections.begin(); it != m_currentSections.end(); ++it)
                {
                    (*it)->Contract();
                }

                UpdateMenuSectionViews(m_currentSections);
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

            void SearchMenuView::SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections)
            {
                m_currentSections = sections;
            }
        }
    }
}