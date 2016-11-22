// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "SearchMenuViewImpl.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuView::SearchMenuView(const std::shared_ptr<WindowsNativeState>& nativeState,
                const std::string& viewClassName)
            {
                m_pImpl = Eegeo_NEW(SearchMenuViewImpl)(nativeState, viewClassName);
            }

            SearchMenuView::~SearchMenuView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void SearchMenuView::SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
            {
                m_pImpl->SetSearchSection(searchSection);
            }

            void SearchMenuView::RemoveSeachKeyboard()
            {
                m_pImpl->RemoveSeachKeyboard();
            }

            void SearchMenuView::SetSearchInProgress(bool inProgress)
            {
                m_pImpl->SetSearchInProgress(inProgress);
            }

            void SearchMenuView::SetEditText(const std::string& searchText, bool isTag)
            {
                m_pImpl->SetEditText(searchText, isTag);
            }

            void SearchMenuView::SetSearchResultCount(int searchResultCount)
            {
                m_pImpl->SetSearchResultCount(searchResultCount);
            }

            void SearchMenuView::CollapseAll()
            {
                m_pImpl->CollapseAll();
            }

            void SearchMenuView::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_pImpl->InsertSearchPeformedCallback(callback);
            }

            void SearchMenuView::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_pImpl->RemoveSearchPeformedCallback(callback);
            }

            void SearchMenuView::SearchPerformed(const std::string& searchQuery)
            {
                m_pImpl->SearchPerformed(searchQuery);
            }

            void SearchMenuView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertSearchClearedCallback(callback);
            }

            void SearchMenuView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveSearchClearedCallback(callback);
            }

            void SearchMenuView::OnSearchCleared()
            {
                m_pImpl->OnSearchCleared();
            }

            void SearchMenuView::InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_pImpl->InsertSearchItemSelectedCallback(callback);
            }

            void SearchMenuView::RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_pImpl->RemoveSearchItemSelectedCallback(callback);
            }

            void SearchMenuView::HandleSearchItemSelected(int index)
            {
                m_pImpl->HandleSearchItemSelected(index);
            }

            void SearchMenuView::UpdateTableAnimation(float dt)
            {
                m_pImpl->UpdateTableAnimation(dt);
            }

            void SearchMenuView::SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections)
            {
                m_pImpl->SetMenuSections(sections);
            }

            void SearchMenuView::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
                m_pImpl->SetTryDragFunc(function);
            }

            void SearchMenuView::ClearTryDragFunc()
            {
                m_pImpl->ClearTryDragFunc();
            }

            float SearchMenuView::GetAnimationProgress() const
            {
                return m_pImpl->GetAnimationProgress();
            }

            bool SearchMenuView::IsAnimating() const
            {
                return m_pImpl->IsAnimating();
            }

            bool SearchMenuView::IsTableAnimating() const
            {
                return m_pImpl->IsTableAnimating();
            }

            void SearchMenuView::UpdateAnimation(float dt)
            {
                m_pImpl->UpdateAnimation(dt);
            }

            void SearchMenuView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {
                m_pImpl->UpdateMenuSectionViews(sections, contentsChanged);
            }

            void SearchMenuView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void SearchMenuView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void SearchMenuView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void SearchMenuView::SetFullyOnScreenOpen()
            {
                m_pImpl->SetFullyOnScreenOpen();
            }

            void SearchMenuView::SetFullyOnScreenClosed()
            {
                m_pImpl->SetFullyOnScreenClosed();
            }

            void SearchMenuView::SetTableCanInteract(bool canInteract)
            {
                m_pImpl->SetTableCanInteract(canInteract);
            }

            void SearchMenuView::InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewClicked(callback);
            }

            void SearchMenuView::RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewClicked(callback);
            }

            void SearchMenuView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewOpened(callback);
            }

            void SearchMenuView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewOpened(callback);
            }

            void SearchMenuView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewClosed(callback);
            }

            void SearchMenuView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewClosed(callback);
            }

            void SearchMenuView::InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnDragStarted(callback);
            }

            void SearchMenuView::RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnDragStarted(callback);
            }

            void SearchMenuView::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->InsertOnDrag(callback);
            }

            void SearchMenuView::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->RemoveOnDrag(callback);
            }

            void SearchMenuView::InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnDragCompleted(callback);
            }

            void SearchMenuView::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnDragCompleted(callback);
            }

            void SearchMenuView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_pImpl->InsertOnItemSelected(callback);
            }

            void SearchMenuView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_pImpl->RemoveOnItemSelected(callback);
            }
        }
    }
}
