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
            }

            VirtualKeyboardView::~VirtualKeyboardView()
            {
                mDestroy();
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
