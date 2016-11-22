// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiView::SearchResultPoiView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(SearchResultPoiViewImpl)(nativeState);
            }

            SearchResultPoiView::~SearchResultPoiView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel& model, bool isPinned)
            {
                m_pImpl->Show(model, isPinned);
            }

            void SearchResultPoiView::Hide()
            {
                m_pImpl->Hide();
            }

            void SearchResultPoiView::UpdateImage(const std::string& url, bool hasImage, const std::vector<unsigned char>* pImageBytes)
            {
                m_pImpl->UpdateImage(url, hasImage, pImageBytes);
            }

            void SearchResultPoiView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertClosedCallback(callback);
            }

            void SearchResultPoiView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveClosedCallback(callback);
            }

            void SearchResultPoiView::HandleCloseClicked()
            {
                m_pImpl->HandleCloseClicked();
            }

            void SearchResultPoiView::InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_pImpl->InsertTogglePinnedCallback(callback);
            }

            void SearchResultPoiView::RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_pImpl->RemoveTogglePinnedCallback(callback);
            }

            void SearchResultPoiView::HandlePinToggleClicked()
            {
                m_pImpl->HandlePinToggleClicked();
            }

            void SearchResultPoiView::CreateVendorSpecificPoiView(const std::string& vendor)
            {
                m_pImpl->CreateVendorSpecificPoiView(vendor);
            }
        }
    }
}
