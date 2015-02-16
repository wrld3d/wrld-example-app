// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
        namespace View
        {
            class SearchResultPoiViewModel : public ISearchResultPoiViewModel, private Eegeo::NonCopyable
            {
                Search::SdkModel::SearchResultModel m_searchResultModel;
                bool m_isPinned;
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                SearchResultPoiOpenableControl m_openable;

            public:
                SearchResultPoiViewModel(Eegeo::Helpers::TIdentity identity,
                                         Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~SearchResultPoiViewModel();

                const Search::SdkModel::SearchResultModel& GetSearchResultModel() const;
                
                bool IsPinned() const;
                
                void ToggleIsPinned();

                bool TryAcquireReactorControl();

                bool IsOpen() const;

                void Open(const Search::SdkModel::SearchResultModel& searchResultModel,
                          bool isPinned);

                void Close();

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            };
        }
    }
}
