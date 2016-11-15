// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkView::WatermarkView(WindowsNativeState& nativeState, const WatermarkData& watermarkData)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.WatermarkView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid, 
					System::String::typeid,
					System::String::typeid,
					System::String::typeid,
					System::String::typeid,
					System::Boolean::typeid));

				m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this),
					gcnew System::String(watermarkData.ImageAssetName().c_str()),
					gcnew System::String(watermarkData.PopupTitle().c_str()),
					gcnew System::String(watermarkData.PopupBody().c_str()),
					gcnew System::String(watermarkData.WebUrl().c_str()),
					gcnew System::Boolean(watermarkData.ShouldShowShadow())));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
				mUpdateWatermarkData.SetupMethod(m_uiViewClass, m_uiView, "UpdateWatermarkData");
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

			void WatermarkView::UpdateWatermarkData(const WatermarkData& watermarkData)
			{
				mUpdateWatermarkData(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.ImageAssetName()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.PopupTitle()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.PopupBody()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.WebUrl()),
					watermarkData.ShouldShowShadow());
			}

			void WatermarkView::SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay)
			{
				// Windows build doesn't really need to implement -- used to align watermark to bottom of screen on portrait devices
			}
        }
    }
}
