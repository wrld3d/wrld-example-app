// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "CallbackCollection.h"
#include "ISearchMenuView.h"
#include "SearchMenuViewIncludes.h"
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
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

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

                void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_callbacks.AddCallback(callback);
                }

                void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_callbacks.RemoveCallback(callback);
                }

                void SearchPerformed(const std::string& searchQuery)
                {
                    m_callbacks.ExecuteCallbacks(searchQuery);
                }
            };
        }
    }
}
