// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationViewImpl.h"
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
            MyPinCreationInitiationViewImpl::MyPinCreationInitiationViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.MyPinCreationButtonView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mShouldOffsetButtonCSharp.SetupMethod(m_uiViewClass, m_uiView, "ShouldOffsetButton");
            }

            MyPinCreationInitiationViewImpl::~MyPinCreationInitiationViewImpl()
            {
                mDestroy();
            }

            void MyPinCreationInitiationViewImpl::OnSelected()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void MyPinCreationInitiationViewImpl::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void MyPinCreationInitiationViewImpl::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void MyPinCreationInitiationViewImpl::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }

            void MyPinCreationInitiationViewImpl::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void MyPinCreationInitiationViewImpl::SetOnScreenStateToIntermediateValue(float screenValue)
            {
                mAnimateToIntermediateOnScreenState(screenValue);
            }

            void MyPinCreationInitiationViewImpl::ShouldOffsetButton(bool shouldOffset)
            {
                mShouldOffsetButtonCSharp(shouldOffset);
            }
        }
    }
}
