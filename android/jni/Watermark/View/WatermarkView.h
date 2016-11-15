// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IWatermarkView.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

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
                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;
            public:
                WatermarkView(AndroidNativeState& nativeState, const WatermarkData& watermarkData);
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
