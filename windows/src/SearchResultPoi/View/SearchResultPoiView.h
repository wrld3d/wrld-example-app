// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "ISearchResultPoiView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

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

            class SearchResultPoiView : public ISearchResultPoiView, Eegeo::NonCopyable
            {
            private:
                WindowsNativeState& m_nativeState;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_togglePinClickedCallbacks;

                Search::SdkModel::SearchResultModel m_model;

                gcroot<System::Type^> m_uiViewClass[SearchVendors::Num];
                gcroot<System::Object^> m_uiView[SearchVendors::Num];
				
				Helpers::ReflectionHelpers::Method<System::Object^, bool> DisplayPoiInfo[SearchVendors::Num];
                Helpers::ReflectionHelpers::Method<void> DismissPoiInfo[SearchVendors::Num];
                Helpers::ReflectionHelpers::Method<System::String^, bool, array<unsigned char, 1>^> UpdateImageData[SearchVendors::Num];
                Helpers::ReflectionHelpers::Method<void> Destroy[SearchVendors::Num];

                int m_currentVendor;

            public:
                SearchResultPoiView(WindowsNativeState& nativeState, bool isInKioskMode);

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
