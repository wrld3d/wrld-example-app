// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class ISearchResultOnMapInFocusViewModel
        {
        public:
            virtual ~ISearchResultOnMapInFocusViewModel() { }
            
            virtual const Search::SearchResultModel& GetSearchResultModel() const = 0;
            
            virtual bool IsOpen() const = 0;
            
            virtual const Eegeo::v2& ScreenLocation() const = 0;
            
            virtual void SelectFocussedResult() = 0;
            
            virtual void Open(Search::SearchResultModel& searchResultModel, const Eegeo::v2& screenPos) = 0;
            
            virtual void Close() = 0;
            
            virtual void UpdateScreenLocation(const Eegeo::v2& screenPos) = 0;
            
            virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;
            
            virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;
            
            virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            
            virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            
            virtual void InsertUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback) = 0;
            
            virtual void RemoveUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback) = 0;
        };
    }
}
