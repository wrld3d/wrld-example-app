// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
#include "ISearchMenuView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuView : public Menu::View::MenuView, public SearchMenu::View::ISearchMenuView
            {
            private:
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_searchItemSelectedCallbacks;

            public:
                SearchMenuView(AndroidNativeState& nativeState,
                               const std::string& viewClassName);

                void SetHeader(const std::string& header, bool queryPending, size_t numResult);

                void HandleSearchClosed();

                void InsertSearchClosed(Eegeo::Helpers::ICallback0& callback);

                void RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback);

                void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection);

				void RemoveSeachKeyboard() {} // TODO: IR

				void DisableEditText() {} // TODO: IR

				void EnableEditText() {} // TODO: IR

				void SetEditText(const std::string& searchText, bool isCategory) {} // TODO: IR

				void SetSearchResultCount(int searchResultCount) {} // TODO: IR

				void CollapseAll() {} // TODO: IR

				void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) {} // TODO: IR
				void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) {} // TODO: IR

				void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) {} // TODO: IR
				void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) {} // TODO: IR

				void InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
				void RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

				void HandleSearchItemSelected(int index);
            };
        }
    }
}
