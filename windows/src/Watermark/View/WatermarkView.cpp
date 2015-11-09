// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkView::WatermarkView(WindowsNativeState& nativeState, const std::string& googleAnalyticsReferrerToken)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromAssembly("ExampleAppWPF", "ExampleAppWPF.WatermarkView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid, System::String::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this), gcnew System::String(googleAnalyticsReferrerToken.c_str())));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
            }

            WatermarkView::~WatermarkView()
            {
                mDestroy();
            }

            void WatermarkView::OnSelected()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void WatermarkView::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void WatermarkView::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void WatermarkView::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }

            void WatermarkView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void WatermarkView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}
