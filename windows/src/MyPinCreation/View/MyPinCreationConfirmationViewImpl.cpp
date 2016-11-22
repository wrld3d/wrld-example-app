// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationViewImpl.h"
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
            MyPinCreationConfirmationViewImpl::MyPinCreationConfirmationViewImpl(const std::shared_ptr<WindowsNativeState>& windowsNativeState)
                : m_nativeState(windowsNativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.MyPinCreationConfirmationView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
            }

            MyPinCreationConfirmationViewImpl::~MyPinCreationConfirmationViewImpl()
            {
                mDestroy();
            }

            void MyPinCreationConfirmationViewImpl::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationViewImpl::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationViewImpl::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationViewImpl::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationViewImpl::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationViewImpl::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void MyPinCreationConfirmationViewImpl::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void MyPinCreationConfirmationViewImpl::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }
        }
    }
}
