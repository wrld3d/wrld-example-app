// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsAppThreadAssertionMacros.h"
#include "SettingsMenuViewImpl.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuViewImpl::SettingsMenuViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState,
                                                 const std::string& viewClassName)
                :Menu::View::MenuViewImpl(nativeState, viewClassName)
            {

            }

            bool SettingsMenuViewImpl::IsTableAnimating() const
            {
                return false;
            }

            void SettingsMenuViewImpl::UpdateTableAnimation(float dt)
            {
            }

            void SettingsMenuViewImpl::SetTableCanInteract(bool canInteract)
            {
            }
        }
    }
}
