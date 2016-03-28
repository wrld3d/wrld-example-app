// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class ISearchResultPoiViewModel
            {
            public:
                virtual ~ISearchResultPoiViewModel() { }

                virtual const Search::SdkModel::SearchResultModel& GetSearchResultModel() const = 0;
                
                virtual bool IsPinned() const = 0;

                virtual void ToggleIsPinned() = 0;
                
                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open(const Search::SdkModel::SearchResultModel& searchResultModel,
                                  bool isPinned) = 0;

                virtual void Close() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() = 0;
            };
        }
    }
}
