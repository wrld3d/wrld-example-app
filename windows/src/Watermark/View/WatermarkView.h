// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IWatermarkView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkView : public IWatermarkView
            {
            private:
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<float> mAnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
                Helpers::ReflectionHelpers::Method<void> mAnimateToInactive;
				Helpers::ReflectionHelpers::Method<System::String^, System::String^, System::String^, System::String^, bool> mUpdateWatermarkData;
            public:
                WatermarkView(WindowsNativeState& nativeState, const WatermarkData& watermarkData);
                ~WatermarkView();

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void OnSelected();

                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

				void UpdateWatermarkData(const WatermarkData& watermarkData);

				void SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay);
            };
        }
    }
}
