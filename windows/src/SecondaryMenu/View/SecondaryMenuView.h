// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
//#include "ISecondaryMenuView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include <string>

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class SecondaryMenuView : public Menu::View::MenuView
            {
            private:
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

                Helpers::ReflectionHelpers::Method<void> DisableEditTextCSharp;
                Helpers::ReflectionHelpers::Method<void> EnableEditTextCSharp;

            public:
                SecondaryMenuView(WindowsNativeState& nativeState,
                                  const std::string& viewClassName);

                void RemoveSeachKeyboard();

                void DisableEditText();

                void EnableEditText();

                void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

                void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

                void OnSearch(const std::string& searchTerm);
            };
        }
    }
}
