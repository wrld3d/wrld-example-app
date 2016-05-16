// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonView.h"
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
            FlattenButtonView::FlattenButtonView(WindowsNativeState& nativeState)
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

            FlattenButtonView::~FlattenButtonView()
            {
                mDestroy();
            }

            void FlattenButtonView::SetToggled(bool toggled)
            {
                mUpdateViewStateBasedOnFlattening(toggled);
            }

            void FlattenButtonView::OnToggle(bool toggled)
            {
                m_callbacks.ExecuteCallbacks(toggled);
            }

            void FlattenButtonView::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void FlattenButtonView::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void FlattenButtonView::SetFullyOffScreen()
            {
                mAnimateToInActive();
            }

            void FlattenButtonView::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void FlattenButtonView::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void FlattenButtonView::SetViewEnabled(bool enabled)
            {
                mSetViewEnabled(System::Boolean(enabled));
            }
        }
    }
}
