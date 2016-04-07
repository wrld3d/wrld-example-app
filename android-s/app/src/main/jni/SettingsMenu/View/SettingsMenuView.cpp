// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidAppThreadAssertionMacros.h"
#include "SettingsMenuView.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuView::SettingsMenuView(AndroidNativeState& nativeState,
                                               const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {

            }
        }
    }
}
