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
                                                 const std::string& viewClassName,
                                                 bool isInKioskMode)
                :Menu::View::MenuView(nativeState, viewClassName, isInKioskMode)
            {

            }

            bool SettingsMenuView::IsTableAnimating() const
            {
                return false;
            }

            void SettingsMenuView::UpdateTableAnimation(float dt)
            {
            }

            void SettingsMenuView::SetTableCanInteract(bool canInteract)
            {
            }
        }
    }
}
