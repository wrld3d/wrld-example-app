// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "CallbackCollection.h"
#include "SearchResultModel.h"
#include "SearchResultPoi.h"
#include "SearchResultOnMapInFocusScreenControl.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapInFocusViewModel : public ISearchResultOnMapInFocusViewModel, private Eegeo::NonCopyable
        {
            bool m_isOpen;
            Eegeo::v2 m_screenPos;
            Search::SearchResultModel m_searchResultModel;
            Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_updateCallbacks;
            SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
            SearchResultOnMapInFocusScreenControl m_screenControl;
            
        public:
            SearchResultOnMapInFocusViewModel(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                              Eegeo::Helpers::TIdentity identity);
            
            ~SearchResultOnMapInFocusViewModel();
            
            const Search::SearchResultModel& GetSearchResultModel() const;
            
            bool IsOpen() const;
            
            const Eegeo::v2& ScreenLocation() const;
            
            void SelectFocussedResult();
            
            void Open(Search::SearchResultModel& searchResultModel, const Eegeo::v2& screenPos);
            
            void Close();
            
            void UpdateScreenLocation(const Eegeo::v2& screenPos);
            
            ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel();
            
            void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            
            void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            
            void InsertUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback);
            
            void RemoveUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback);
            
        };
    }
}
