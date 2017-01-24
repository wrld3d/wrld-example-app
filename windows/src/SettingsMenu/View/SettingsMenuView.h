// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include <string>

#include "ReflectionHelpers.h"
#include "MenuView.h"
#include "IMenuSectionViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuView : public Menu::View::MenuView
            {
                typedef std::vector<Menu::View::IMenuSectionViewModel*> TSections;

            private:
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

            public:
                SettingsMenuView(WindowsNativeState& nativeState,
                                  const std::string& viewClassName,
                                  bool isInKioskMode);

                 bool IsTableAnimating() const;

                 void UpdateTableAnimation(float dt);

                 void SetTableCanInteract(bool canInteract);
            };
        }
    }
}
