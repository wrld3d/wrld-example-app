// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "ISearchResultPoiView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            enum SearchVendors
            {
                Yelp = 0,
                eeGeo,
                GeoNames,
                Num
            };

            class SearchResultPoiViewImpl;

            class SearchResultPoiView : public ISearchResultPoiView, Eegeo::NonCopyable
            {
            private:
                SearchResultPoiViewImpl* m_pImpl;
            public:
                SearchResultPoiView(const std::shared_ptr<WindowsNativeState>& nativeState);

                ~SearchResultPoiView();

                void Show(const Search::SdkModel::SearchResultModel& model, bool isPinned);

                void Hide();

                void UpdateImage(const std::string& url, bool hasImage, const std::vector<unsigned char>* pImageBytes);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleCloseClicked();

                void InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);

                void RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);

                void HandlePinToggleClicked();

                void CreateVendorSpecificPoiView(const std::string& vendor);
            };
        }
    }
}
