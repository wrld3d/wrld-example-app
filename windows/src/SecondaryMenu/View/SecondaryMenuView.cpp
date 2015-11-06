// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsAppThreadAssertionMacros.h"
#include "SecondaryMenuView.h"
#include "ReflectionHelpers.h"

#using "mscorlib.dll"

#include<vcclr.h>
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            SecondaryMenuView::SecondaryMenuView(WindowsNativeState& nativeState,
                                                 const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
                DisableEditTextCSharp.SetupMethod(m_uiViewClass, m_uiView, "DisableEditText");
                EnableEditTextCSharp.SetupMethod(m_uiViewClass, m_uiView, "EnableEditText");
            }

            void SecondaryMenuView::RemoveSeachKeyboard()
            {
                //CallVoidVoidMethod("RemoveSeachKeyboard");
            }

            void SecondaryMenuView::DisableEditText()
            {
                DisableEditTextCSharp();
            }

            void SecondaryMenuView::EnableEditText()
            {
                EnableEditTextCSharp();
            }

            void SecondaryMenuView::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void SecondaryMenuView::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void SecondaryMenuView::OnSearch(const std::string& searchTerm)
            {
                m_callbacks.ExecuteCallbacks(searchTerm);
            }
        }
    }
}
