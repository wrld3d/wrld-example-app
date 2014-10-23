// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultModel.h"
#include "CallbackCollection.h"
#include "SearchResultPoiOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        class SearchResultPoiViewModel : public ISearchResultPoiViewModel, private Eegeo::NonCopyable
        {
            Search::SearchResultModel m_searchResultModel;
            Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
            SearchResultPoiOpenableControl m_openable;
            
        public:
            SearchResultPoiViewModel(Eegeo::Helpers::TIdentity identity,
                                     Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~SearchResultPoiViewModel();
            
            const Search::SearchResultModel& GetSearchResultModel() const;

            bool TryAcquireReactorControl();
            
            bool IsOpen() const;
            
            void Open(Search::SearchResultModel& searchResultModel);
            
            void Close();
            
            OpenableControlViewModel::IOpenableControlViewModel& GetOpenableControl();
            
            void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            
            void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
        };
    }
}
