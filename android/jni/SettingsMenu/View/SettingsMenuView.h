// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
#include "ISettingsMenuView.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"

#include <string>

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuView : public Menu::View::MenuView, public ISettingsMenuView
            {
            public:
                SettingsMenuView(const std::shared_ptr<AndroidNativeState>& nativeState,
                		const std::string& viewClassName);
            };
        }
    }
}
