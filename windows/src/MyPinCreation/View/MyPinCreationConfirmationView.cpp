// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationView::MyPinCreationConfirmationView(WindowsNativeState& windowsNativeState)
                : m_nativeState(windowsNativeState)
            {
                m_uiViewClass = GetTypeFromAssembly("ExampleAppWPF", "ExampleAppWPF.MyPinCreationConfirmationView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
            }

            MyPinCreationConfirmationView::~MyPinCreationConfirmationView()
            {
                mDestroy();
            }

            void MyPinCreationConfirmationView::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationView::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationView::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void MyPinCreationConfirmationView::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void MyPinCreationConfirmationView::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }
        }
    }
}
