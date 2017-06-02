// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "ISearchMenuView.h"
#include "WindowsNativeState.h"
#include "MenuView.h"

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

                Helpers::ReflectionHelpers::Method<System::String^, array<System::String^>^> mSetSearchSection;
                Helpers::ReflectionHelpers::Method<void> mSetSearchInProgress;
                Helpers::ReflectionHelpers::Method<void> mSetSearchEnded;
                Helpers::ReflectionHelpers::Method<System::String^, bool> mSetEditText;
                Helpers::ReflectionHelpers::Method<void> mGetEditText;
                Helpers::ReflectionHelpers::Method<void> mHasTagSearch;
                Helpers::ReflectionHelpers::Method<int> mSetSearchResultCount;
                Helpers::ReflectionHelpers::Method<void> mHideSearchResultCount;
                Helpers::ReflectionHelpers::Method<void> mRemoveSearchQueryResults;

                std::vector<Menu::View::IMenuSectionViewModel*> m_currentSections;

            public:
                SearchMenuView(WindowsNativeState& nativeState,
                    const std::string& viewClassName,
                    bool isInKioskMode);

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

                bool IsTableAnimating() const;

                void UpdateTableAnimation(float dt);

                void SetTableCanInteract(bool interact);

                void SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections);
            };
        }
    }
}
