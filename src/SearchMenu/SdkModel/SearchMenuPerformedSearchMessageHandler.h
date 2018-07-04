// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "SearchMenuSearchWithContextMessage.h"
#include "AutocompleteSuggestionsMessage.h"
#include "ISearchQueryPerformer.h"
#include "IAutocompleteSuggestionQueryPerformer.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class SearchMenuPerformedSearchMessageHandler : private Eegeo::NonCopyable
            {
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                Search::SdkModel::IAutocompleteSuggestionQueryPerformer& m_autocompleteSuggestionsQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const SearchMenuPerformedSearchMessage&> m_handlePerformedSearchMessageBinding;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const SearchMenuSearchWithContextMessage&> m_handleSearchWithContextMessageBinding;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const AutocompleteSuggestionsMessage&> m_handleAutocompleteSuggestionsMessageBinding;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const AutocompleteSuggestionsCancelledMessage&> m_handleAutocompleteSuggestionsCancelledMessageBinding;

                Metrics::IMetricsService& m_metricsService;
                
                void OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message);
                void OnSearchWithContextMessage(const SearchMenuSearchWithContextMessage& message);
                void OnAutocompleteSuggestionsMessage(const AutocompleteSuggestionsMessage& message);
                void OnAutocompleteSuggestionsCancelledMessage(const AutocompleteSuggestionsCancelledMessage& message);
            public:
                SearchMenuPerformedSearchMessageHandler(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                        Search::SdkModel::IAutocompleteSuggestionQueryPerformer& autocompleteSuggestionsQueryPerformer,
                                                        ExampleAppMessaging::TMessageBus& messageBus,
                                                        Metrics::IMetricsService& metricsService);
                
                ~SearchMenuPerformedSearchMessageHandler();
            };
        }
    }
}
