// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "FlattenButtonCLI.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonViewImpl::FlattenButtonViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.FlattenButtonView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mUpdateViewStateBasedOnFlattening.SetupMethod(m_uiViewClass, m_uiView, "UpdateViewStateBasedOnFlattening");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
                mSetViewEnabled.SetupMethod(m_uiViewClass, m_uiView, "SetViewEnabled");
            }

            FlattenButtonViewImpl::~FlattenButtonViewImpl()
            {
                mDestroy();
            }

            void FlattenButtonViewImpl::SetToggled(bool toggled)
            {
                mUpdateViewStateBasedOnFlattening(toggled);
            }

            void FlattenButtonViewImpl::OnToggle(bool toggled)
            {
                m_callbacks.ExecuteCallbacks(toggled);
            }

            void FlattenButtonViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void FlattenButtonViewImpl::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void FlattenButtonViewImpl::SetFullyOffScreen()
            {
                mAnimateToInActive();
            }

            void FlattenButtonViewImpl::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void FlattenButtonViewImpl::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void FlattenButtonViewImpl::SetViewEnabled(bool enabled)
            {
                mSetViewEnabled(System::Boolean(enabled));
            }
        }
    }
}