// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewInterop::SearchResultPoiViewInterop(SearchResultPoiViewContainer* pView) : m_pView(pView)
            {
            }

            void SearchResultPoiViewInterop::Show(const Search::SdkModel::SearchResultModel& model,
                                                  bool isPinned)
            {
                [m_pView open:&model :isPinned];
            }

            void SearchResultPoiViewInterop::Hide()
            {
                [m_pView close];
            }
            
            void SearchResultPoiViewInterop::UpdateImage(const std::string& url,
                                                         bool hasImage,
                                                         const std::vector<Byte>* imageBytes)
            {
                [m_pView updateImage :url :hasImage bytes:imageBytes];
            }

            void SearchResultPoiViewInterop::InsertAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
            {
                m_availabilityChangedCallbacks.AddCallback(callback);
            }
            
            void SearchResultPoiViewInterop::RemoveAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
            {
                m_availabilityChangedCallbacks.RemoveCallback(callback);
            }
            
            void SearchResultPoiViewInterop::HandleAvailabilityChanged(const Search::SdkModel::SearchResultModel& searchResultModel, const std::string& availability)
            {
                m_availabilityChangedCallbacks.ExecuteCallbacks(searchResultModel, availability);
            }
            
            void SearchResultPoiViewInterop::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeClickedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiViewInterop::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeClickedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiViewInterop::HandleCloseClicked()
            {
                m_closeClickedCallbacks.ExecuteCallbacks();
            }
            
            void SearchResultPoiViewInterop::InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_togglePinClickedCallbacks.AddCallback(callback);
            }
            
            void SearchResultPoiViewInterop::RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_togglePinClickedCallbacks.RemoveCallback(callback);
            }
            
            void SearchResultPoiViewInterop::HandlePinToggleClicked(Search::SdkModel::SearchResultModel& searchResultModel)
            {
                m_togglePinClickedCallbacks.ExecuteCallbacks(searchResultModel);
            }
        }
    }
}