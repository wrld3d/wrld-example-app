// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include "Watermark.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class IWatermarkView : public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~IWatermarkView() { };
                
                virtual void OnSelected() = 0;
                virtual void UpdateWatermarkData(const WatermarkData& watermarkData) = 0;
                virtual void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay) = 0;
            };
        }
    }
}
