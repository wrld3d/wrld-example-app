// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "ISearchMenuView.h"
#include "WindowsNativeState.h"
#include "IMenuView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewImpl;

            class SearchMenuView : public Menu::View::IMenuView, public SearchMenu::View::ISearchMenuView
            {
            private:
                SearchMenuViewImpl* m_pImpl;

            public:
                SearchMenuView(const std::shared_ptr<WindowsNativeState>& nativeState,
                               const std::string& viewClassName);

                ~SearchMenuView();

                void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection);

                void RemoveSeachKeyboard();

                void SetSearchInProgress(bool inProgress);

                void SetEditText(const std::string& searchText, bool isTag);

                void SetSearchResultCount(int searchResultCount);

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

                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function);

                void ClearTryDragFunc();

                float GetAnimationProgress() const;

                bool IsAnimating() const;

                void UpdateAnimation(float dt);

                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();
                void SetFullyOnScreenOpen();
                void SetFullyOnScreenClosed();

                void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback);

                void InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback);

                void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback);
                void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback);

                void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback);

                void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);
            };
        }
    }
}
