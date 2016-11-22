// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewImpl.h"
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
            SearchMenuViewImpl::SearchMenuViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState,
                const std::string& viewClassName)
                : Menu::View::MenuViewImpl(nativeState, viewClassName)
                , m_currentSections(0)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.SearchMenuView");

                mSetSearchSection.SetupMethod(m_uiViewClass, m_uiView, "SetSearchSection");
                mSetSearchInProgress.SetupMethod(m_uiViewClass, m_uiView, "SetSearchInProgress");
                mSetSearchEnded.SetupMethod(m_uiViewClass, m_uiView, "SetSearchEnded");
                mSetEditText.SetupMethod(m_uiViewClass, m_uiView, "SetEditText");
                mSetSearchResultCount.SetupMethod(m_uiViewClass, m_uiView, "SetSearchResultCount");
            }

            void SearchMenuViewImpl::SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
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

            void SearchMenuViewImpl::RemoveSeachKeyboard()
            {
                
            }

            void SearchMenuViewImpl::SetSearchInProgress(bool inProgress)
            {
                if (inProgress)
                {
                    mSetSearchInProgress();
                }
                else
                {
                    mSetSearchEnded();
                }
            }

            void SearchMenuViewImpl::SetEditText(const std::string& searchText, bool isTag)
            {
                mSetEditText(gcnew System::String(searchText.c_str()), isTag);
            }

            void SearchMenuViewImpl::SetSearchResultCount(int searchResultCount)
            {
                mSetSearchResultCount(searchResultCount);
            }

            void SearchMenuViewImpl::CollapseAll()
            {
                for (Menu::View::TSections::iterator it = m_currentSections.begin(); it != m_currentSections.end(); ++it)
                {
                    (*it)->Contract();
                }

                UpdateMenuSectionViews(m_currentSections, false);
            }

            void SearchMenuViewImpl::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchPerformedCallbacks.AddCallback(callback);
            }

            void SearchMenuViewImpl::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchPerformedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuViewImpl::SearchPerformed(const std::string& searchQuery)
            {
                m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
            }

            void SearchMenuViewImpl::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchMenuViewImpl::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuViewImpl::OnSearchCleared()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
            }

            void SearchMenuViewImpl::InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_searchItemSelectedCallbacks.AddCallback(callback);
            }

            void SearchMenuViewImpl::RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_searchItemSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchMenuViewImpl::HandleSearchItemSelected(int index)
            {
               m_searchItemSelectedCallbacks.ExecuteCallbacks(index);
            }

            bool SearchMenuViewImpl::IsTableAnimating() const
            {
                return false;
            }

            void SearchMenuViewImpl::UpdateTableAnimation(float dt)
            {

            }

            void SearchMenuViewImpl::SetTableCanInteract(bool interact)
            {

            }

            void SearchMenuViewImpl::SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections)
            {
                m_currentSections = sections;
            }
        }
    }
}
