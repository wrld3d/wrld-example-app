// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsAppThreadAssertionMacros.h"
#include "SettingsMenuView.h"
#include "SettingsMenuViewImpl.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuView::SettingsMenuView(const std::shared_ptr<WindowsNativeState>& nativeState,
                                                 const std::string& viewClassName)
            {
                m_pImpl = Eegeo_NEW(SettingsMenuViewImpl)(nativeState, viewClassName);
            }

            SettingsMenuView::~SettingsMenuView()
            {
                Eegeo_DELETE m_pImpl;
            }

            bool SettingsMenuView::IsTableAnimating() const
            {
                return m_pImpl->IsTableAnimating();
            }

            void SettingsMenuView::UpdateTableAnimation(float dt)
            {
                m_pImpl->UpdateTableAnimation(dt);
            }

            void SettingsMenuView::SetTableCanInteract(bool canInteract)
            {
                m_pImpl->SetTableCanInteract(canInteract);
            }
            
            void SettingsMenuView::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
                m_pImpl->SetTryDragFunc(function);
            }

            void SettingsMenuView::ClearTryDragFunc()
            {
                m_pImpl->ClearTryDragFunc();
            }

            float SettingsMenuView::GetAnimationProgress() const
            {
                return m_pImpl->GetAnimationProgress();
            }

            bool SettingsMenuView::IsAnimating() const
            {
                return m_pImpl->IsAnimating();
            }

            void SettingsMenuView::UpdateAnimation(float dt)
            {
                m_pImpl->UpdateAnimation(dt);
            }

            void SettingsMenuView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {
                m_pImpl->UpdateMenuSectionViews(sections, contentsChanged);
            }

            void SettingsMenuView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void SettingsMenuView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void SettingsMenuView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void SettingsMenuView::SetFullyOnScreenOpen()
            {
                m_pImpl->SetFullyOnScreenOpen();
            }

            void SettingsMenuView::SetFullyOnScreenClosed()
            {
                m_pImpl->SetFullyOnScreenClosed();
            }

            void SettingsMenuView::InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewClicked(callback);
            }

            void SettingsMenuView::RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewClicked(callback);
            }

            void SettingsMenuView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewOpened(callback);
            }

            void SettingsMenuView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewOpened(callback);
            }

            void SettingsMenuView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnViewClosed(callback);
            }

            void SettingsMenuView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnViewClosed(callback);
            }

            void SettingsMenuView::InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnDragStarted(callback);
            }

            void SettingsMenuView::RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnDragStarted(callback);
            }

            void SettingsMenuView::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->InsertOnDrag(callback);
            }

            void SettingsMenuView::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->RemoveOnDrag(callback);
            }

            void SettingsMenuView::InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertOnDragCompleted(callback);
            }

            void SettingsMenuView::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveOnDragCompleted(callback);
            }

            void SettingsMenuView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_pImpl->InsertOnItemSelected(callback);
            }

            void SettingsMenuView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_pImpl->RemoveOnItemSelected(callback);
            }
        }
    }
}
