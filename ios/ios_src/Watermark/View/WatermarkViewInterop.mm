// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewInterop.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            void WatermarkViewInterop::OnSelected()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void WatermarkViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue:value];
            }

            void WatermarkViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }

            void WatermarkViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }

            void WatermarkViewInterop::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void WatermarkViewInterop::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void WatermarkViewInterop::UpdateWatermarkData(const WatermarkData& watermarkData)
            {
                [m_pView updateWatermarkData: watermarkData];
            }
            
            void WatermarkViewInterop::SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay)
            {
                [m_pView setWatermarkAlignmentState:alignAlongBottom :alignBelowFloorDisplay];
            }
        }
    }
}
