// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkViewImpl::WatermarkViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
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
					gcnew System::String("eegeo_logo"),
					gcnew System::String(""),
					gcnew System::String(""),
					gcnew System::String(""),
					gcnew System::Boolean(false)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
				mUpdateWatermarkData.SetupMethod(m_uiViewClass, m_uiView, "UpdateWatermarkData");
            }

            WatermarkViewImpl::~WatermarkViewImpl()
            {
                mDestroy();
            }

            void WatermarkViewImpl::OnSelected()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void WatermarkViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void WatermarkViewImpl::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void WatermarkViewImpl::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }

            void WatermarkViewImpl::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void WatermarkViewImpl::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

			void WatermarkViewImpl::UpdateWatermarkData(const WatermarkData& watermarkData)
			{
				mUpdateWatermarkData(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.ImageAssetName()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.PopupTitle()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.PopupBody()),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(watermarkData.WebUrl()),
					watermarkData.ShouldShowShadow());
			}

			void WatermarkViewImpl::SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay)
			{
				// Windows build doesn't really need to implement -- used to align watermark to bottom of screen on portrait devices
			}
        }
    }
}
