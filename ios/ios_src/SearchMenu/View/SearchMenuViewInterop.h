// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "CallbackCollection.h"
#include "ISearchMenuView.h"
#include "SearchMenuViewIncludes.h"
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

            public:
                SearchMenuViewInterop(SearchMenuView* pView)
                    : m_pView(pView)
                {
                }

                void RemoveSeachKeyboard()
                {
                    [m_pView removeSeachKeyboard];
                }

                void DisableEditText()
                {
                    [m_pView disableEdit];
                }

                void EnableEditText()
                {
                    [m_pView enableEdit];
                }
                
                void SetEditText(const std::string& searchText, bool isCategory)
                {
                    [m_pView setEditText :[NSString stringWithUTF8String:searchText.c_str()] :isCategory];
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
            };
        }
    }
}
