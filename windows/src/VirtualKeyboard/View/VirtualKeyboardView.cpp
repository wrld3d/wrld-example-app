// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "BidirectionalBus.h"
#include "ReflectionHelpers.h"
#include "VirtualKeyboardStateChangedMessage.h"
#include "VirtualKeyboardView.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace VirtualKeyboard
    {
        namespace View
        {
            VirtualKeyboardView::VirtualKeyboardView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.VirtualKeyboardView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mHideVirtualKeyboard.SetupMethod(m_uiViewClass, m_uiView, "HideVirtualKeyboard");
				mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
				mAddCustomKeyboardKey.SetupMethod(m_uiViewClass, m_uiView, "AddCustomKeyboardKey");
				mClearCustomKeyboardKeys.SetupMethod(m_uiViewClass, m_uiView, "ClearCustomKeyboardKeys");
            }

            VirtualKeyboardView::~VirtualKeyboardView()
            {
                mDestroy();
            }

			void VirtualKeyboardView::AddCustomKeyboardLayout(std::vector<std::vector<std::string>> customKeyboardLayout)
			{
				mClearCustomKeyboardKeys();

				for(int i = 0; i < customKeyboardLayout.size(); i++)
				{
					mAddCustomKeyboardKey(
						gcnew String(customKeyboardLayout[i][0].c_str()), // Row
						gcnew String(customKeyboardLayout[i][1].c_str()), // Index
						gcnew String(customKeyboardLayout[i][2].c_str()), // Lowercase
						gcnew String(customKeyboardLayout[i][3].c_str())); // Uppercase
				}
			}

            void VirtualKeyboardView::OnVisibilityChanged(const bool isVisible)
            {
                m_messageBus.Publish(VirtualKeyboardStateChangedMessage(isVisible));
            }

            void VirtualKeyboardView::HideVirtualKeyboard()
            {
                mHideVirtualKeyboard();
            }
        }
    }
}
