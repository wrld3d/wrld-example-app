// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassView.h"
#include "CompassViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassView::CompassView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(CompassViewImpl)(nativeState);
            }

            CompassView::~CompassView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void CompassView::OnCycle()
            {
                m_pImpl->OnCycle();
            }

            void CompassView::ShowGpsDisabledView()
            {
                m_pImpl->ShowGpsDisabledView();
            }

            void CompassView::ShowGpsFollowView()
            {
                m_pImpl->ShowGpsFollowView();
            }

            void CompassView::ShowGpsCompassModeView()
            {
                m_pImpl->ShowGpsCompassModeView();
            }

            void CompassView::NotifyGpsUnauthorized()
            {
                m_pImpl->NotifyGpsUnauthorized();
            }

            void CompassView::SetHeadingRadians(float heading)
            {
                m_pImpl->SetHeadingRadians(heading);
            }

            void CompassView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void CompassView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void CompassView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void CompassView::InsertCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertCycledCallback(callback);
            }

            void CompassView::RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveCycledCallback(callback);
            }
        }
    }
}
