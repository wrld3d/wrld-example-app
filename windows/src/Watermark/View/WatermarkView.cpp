// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WatermarkViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkView::WatermarkView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(WatermarkViewImpl)(nativeState);
            }

            WatermarkView::~WatermarkView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void WatermarkView::OnSelected()
            {
                m_pImpl->OnSelected();
            }

            void WatermarkView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void WatermarkView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void WatermarkView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void WatermarkView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertSelectedCallback(callback);
            }

            void WatermarkView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveSelectedCallback(callback);
            }

			void WatermarkView::UpdateWatermarkData(const WatermarkData& watermarkData)
			{
                m_pImpl->UpdateWatermarkData(watermarkData);
			}

			void WatermarkView::SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay)
			{
                m_pImpl->SetWatermarkAlignmentState(alignAlongBottom, alignBelowFloorDisplay);
			}
        }
    }
}
