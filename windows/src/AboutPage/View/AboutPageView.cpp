// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageView.h"
#include "AboutPageViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageView::AboutPageView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(AboutPageViewImpl)(nativeState);
            }

            AboutPageView::~AboutPageView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void AboutPageView::CloseTapped()
            {
                m_pImpl->CloseTapped();
            }

            void AboutPageView::Open()
            {
                m_pImpl->Open();
            }

            void AboutPageView::Close()
            {
                m_pImpl->Close();
            }

            void AboutPageView::SetContent(const std::string& content)
            {
                m_pImpl->SetContent(content);
            }

            void AboutPageView::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertCloseTappedCallback(callback);
            }

            void AboutPageView::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveCloseTappedCallback(callback);
            }
        }
    }
}
