// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include <string>

#include "ReflectionHelpers.h"
#include "MenuViewImpl.h"
#include "IMenuSectionViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewImpl : public Menu::View::MenuViewImpl
            {
                typedef std::vector<Menu::View::IMenuSectionViewModel*> TSections;

            private:
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

            public:
                SettingsMenuViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState,
                                  const std::string& viewClassName);

                 bool IsTableAnimating() const;

                 void UpdateTableAnimation(float dt);

                 void SetTableCanInteract(bool canInteract);
            };
        }
    }
}
