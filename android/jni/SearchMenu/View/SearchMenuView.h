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
                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_searchItemSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;

                void CallVoidVoidMethod(const char* func);

            public:
                SearchMenuView(AndroidNativeState& nativeState,
                               const std::string& viewClassName);

                void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection);

				void RemoveSeachKeyboard();

				void SetSearchInProgress(bool inProgress);

				void SetEditText(const std::string& searchText, bool isTag);
				std::string GetEditText();

				bool HasTagSearch();

				void SetSearchResultCount(int searchResultCount);
				void HideSearchResultCount();
				void RemoveSearchQueryResults();

				void CollapseAll();

				void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
				void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

				void SearchPerformed(const std::string& searchQuery);

				void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
				void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);

				void OnSearchCleared();

				void InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
				void RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

				void HandleSearchItemSelected(int index);

				// Override of Menu ItemSelected to allow expansion of a section to trigger clear search
				void HandleItemSelected(int sectionIndex, int itemIndex);

				void SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections);
            };
        }
    }
}
