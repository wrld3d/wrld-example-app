// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "CallbackCollection.h"
#include "ISearchMenuView.h"
#include "IMenuSectionViewModel.h"
#include "SearchMenuView.h"
#include "SearchResultViewClearedMessage.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewInterop : private Eegeo::NonCopyable, public ISearchMenuView
            {
            private:
                SearchMenuView* m_pView;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_searchItemSelectedCallbacks;

            public:
                SearchMenuViewInterop(SearchMenuView* pView)
                    : m_pView(pView)
                {
                }
                
                virtual void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
                {
                    [m_pView setSearchSection:&searchSection];
                }

                void RemoveSeachKeyboard()
                {
                    [m_pView.pInputDelegate removeSeachKeyboard];
                }

                void SetSearchInProgress(bool inProgress)
                {
                    if(inProgress)
                    {
                        [m_pView.pInputDelegate setSearchInProgress];
                    }
                    else
                    {
                        [m_pView.pInputDelegate setSearchEnded];
                    }
                }
                
                void SetEditText(const std::string& searchText, bool isTag)
                {
                    [m_pView.pInputDelegate setEditText :[NSString stringWithUTF8String:searchText.c_str()] :isTag];
                }
                
                std::string GetEditText()
                {
                    return [m_pView.pInputDelegate getEditText];
                }
                
                bool HasTagSearch()
                {
                    return [m_pView.pInputDelegate hasTagSearch];
                }
                
                void SetSearchResultCount(int searchResultCount)
                {
                    [m_pView setSearchResultCount:searchResultCount];
                }
                
                void HideSearchResultCount()
                {
                    [m_pView hideSearchResultCount];
                }
                
                void RemoveSearchQueryResults()
                {
                    [m_pView removeSearchQueryResults];
                }

                void CollapseAll()
                {
                    [m_pView collapseAll];
                }
                
                void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_searchPerformedCallbacks.AddCallback(callback);
                }

                void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_searchPerformedCallbacks.RemoveCallback(callback);
                }

                void SearchPerformed(const std::string& searchQuery)
                {
                    m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
                }
                
                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_searchClearedCallbacks.AddCallback(callback);
                }
                
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_searchClearedCallbacks.RemoveCallback(callback);
                }
                
                void OnSearchCleared()
                {
                    m_searchClearedCallbacks.ExecuteCallbacks();
                }
                
                void InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
                {
                    m_searchItemSelectedCallbacks.AddCallback(callback);
                }
                
                void RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
                {
                    m_searchItemSelectedCallbacks.RemoveCallback(callback);
                }
                
                void HandleSearchItemSelected(int index)
                {
                    m_searchItemSelectedCallbacks.ExecuteCallbacks(index);
                }
                
                void SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections)
                {
                    
                }
            };
        }
    }
}
