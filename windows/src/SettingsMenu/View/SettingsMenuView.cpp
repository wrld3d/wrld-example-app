// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsAppThreadAssertionMacros.h"
#include "SettingsMenuView.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuView::SettingsMenuView(WindowsNativeState& nativeState,
                                                 const std::string& viewClassName)
            {

            }
            void SettingsMenuView::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
            }
            void SettingsMenuView::ClearTryDragFunc()
            {
            }
            void SettingsMenuView::SetOnScreenStateToIntermediateValue(float value)
            {
            }
            void SettingsMenuView::SetFullyOnScreen()
            {
            }
            void SettingsMenuView::SetFullyOffScreen()
            {
            }
            float SettingsMenuView::GetAnimationProgress() const
            {
                return 0.0f;
            }
            bool SettingsMenuView::IsAnimating() const
            {
                return false;
            }
            bool SettingsMenuView::IsTableAnimating() const
            {
                return false;
            }
            void SettingsMenuView::UpdateAnimation(float dt)
            {
            }
            void SettingsMenuView::UpdateTableAnimation(float dt)
            {
            }
            void SettingsMenuView::UpdateMenuSectionViews(TSections & sections)
            {
            }
            void SettingsMenuView::SetFullyOnScreenOpen()
            {
            }
            void SettingsMenuView::SetFullyOnScreenClosed()
            {
            }
            void SettingsMenuView::SetTableCanInteract(bool canInteract)
            {
            }
            void SettingsMenuView::InsertOnViewClicked(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::RemoveOnViewClicked(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::InsertOnViewOpened(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::InsertOnViewClosed(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::InsertOnDragStarted(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::RemoveOnDragStarted(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
            }
            void SettingsMenuView::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
            }
            void SettingsMenuView::InsertOnDragCompleted(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0 & callback)
            {
            }
            void SettingsMenuView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
            }
            void SettingsMenuView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
            }
        }
    }
}
