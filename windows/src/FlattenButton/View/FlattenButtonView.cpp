// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonView.h"
#include "FlattenButtonViewImpl.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonView::FlattenButtonView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(FlattenButtonViewImpl)(nativeState);
            }

            FlattenButtonView::~FlattenButtonView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void FlattenButtonView::SetToggled(bool toggled)
            {
                m_pImpl->SetToggled(toggled);
            }

            void FlattenButtonView::OnToggle(bool toggled)
            {
                m_pImpl->OnToggle(toggled);
            }

            void FlattenButtonView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void FlattenButtonView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void FlattenButtonView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void FlattenButtonView::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_pImpl->InsertToggleCallback(callback);
            }

            void FlattenButtonView::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_pImpl->RemoveToggleCallback(callback);
            }

            void FlattenButtonView::SetViewEnabled(bool enabled)
            {
                m_pImpl->SetViewEnabled(enabled);
            }
        }
    }
}
