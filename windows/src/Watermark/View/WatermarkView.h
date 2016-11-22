// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IWatermarkView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkViewImpl;

            class WatermarkView : public IWatermarkView
            {
            private:
                WatermarkViewImpl* m_pImpl;
                
            public:
                WatermarkView(const std::shared_ptr<WindowsNativeState>& nativeState);
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
